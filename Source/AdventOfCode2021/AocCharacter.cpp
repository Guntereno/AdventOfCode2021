// Fill out your copyright notice in the Description page of Project Settings.


#include "AocCharacter.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Interactable.h"

// Sets default values
AAocCharacter::AAocCharacter() :
	PitchRate{ 90 },
	YawRate{ 90 },
	Reach{ 300 }
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAocCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAocCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickInteraction();
}

void AAocCharacter::TickInteraction()
{
	// If the user is no longer looking at the interactable, we need to stop the interaction
	if (CurrentInteractable != nullptr)
	{
		AActor* Actor = GetFirstInteractableInReach();
		if (Actor != CurrentInteractable)
		{
			StopInteracting();
		}
	}
}

// Called to bind functionality to input
void AAocCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AAocCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAocCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Pitch", this, &AAocCharacter::Pitch);
	PlayerInputComponent->BindAxis("Yaw", this, &AAocCharacter::Yaw);
	PlayerInputComponent->BindAxis("PitchImmediate", this, &AAocCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("YawImmediate", this, &AAocCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &AAocCharacter::Interact);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Released, this, &AAocCharacter::StopInteracting);
}

void AAocCharacter::MoveForward(float Value)
{
	if ((Controller == nullptr) || (Value == 0.0f))
	{
		return;
	}

	const FRotator Rotation{ Controller->GetControlRotation() };
	const FRotator YawRotation{ 0.0f, Rotation.Yaw, 0.0f };
	const FVector Direction{ FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::X) };
	AddMovementInput(Direction, Value);
}

void AAocCharacter::MoveRight(float Value)
{
	if ((Controller == nullptr) || (Value == 0.0f))
	{
		return;
	}

	const FRotator Rotation{ Controller->GetControlRotation() };
	const FRotator YawRotation{ 0.0f, Rotation.Yaw, 0.0f };
	const FVector Direction{ FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::Y) };
	AddMovementInput(Direction, Value);
}

void AAocCharacter::Pitch(float Value)
{
	AddControllerPitchInput(Value * PitchRate * GetWorld()->GetDeltaSeconds());
}

void AAocCharacter::Yaw(float Value)
{
	AddControllerYawInput(Value * YawRate * GetWorld()->GetDeltaSeconds());
}

inline void AAocCharacter::AddControllerYawInput(float Value)
{
	APawn::AddControllerYawInput(Value);
}

inline void AAocCharacter::AddControllerPitchInput(float Value)
{
	APawn::AddControllerPitchInput(Value);
}

void AAocCharacter::Interact()
{
	AActor* Interactable = GetFirstInteractableInReach();
	if (Interactable != nullptr)
	{
		//UE_LOG(LogTemp, Display, TEXT("Interacting with '%s'"), *(Interactable->GetName()));
		CurrentInteractable = Interactable;
		IInteractable::Execute_Interact(CurrentInteractable);
	}
}

void AAocCharacter::StopInteracting()
{
	if (CurrentInteractable != nullptr)
	{
		IInteractable::Execute_StopInteracting(CurrentInteractable);
		CurrentInteractable = nullptr;
	}
}

void AAocCharacter::GetRay(FVector& Origin, FVector& Target) const
{
	FRotator RayRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Origin, RayRotation);
	Target = Origin + (RayRotation.Vector() * Reach);
}

bool AAocCharacter::GetFirstActorInReach(FHitResult& HitResult) const
{
	FVector RayOrigin, RayTarget;
	GetRay(RayOrigin, RayTarget);

	return GetFirstActorInReach(RayOrigin, RayTarget, HitResult);
}

bool AAocCharacter::GetFirstActorInReach(
	const FVector& RayOrigin,
	const FVector& RayTarget,
	FHitResult& HitResult) const
{
	//DrawDebugLine(
	//	GetWorld(),
	//	RayOrigin,
	//	RayTarget,
	//	FColor::Magenta,
	//	false,
	//	2.0f,
	//	0U,
	//	1.0f
	//);

	const FCollisionQueryParams QueryParams(FName(), false, GetOwner());
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		RayOrigin, RayTarget,
		ECollisionChannel::ECC_Visibility,
		QueryParams);
	return bHit;
}

AActor* AAocCharacter::GetFirstInteractableInReach() const
{
	FHitResult HitResult;
	GetFirstActorInReach(HitResult);
	if (HitResult.bBlockingHit)
	{
		AActor* Actor = HitResult.GetActor();
		IInteractable* Interactable = Cast<IInteractable>(Actor);
		if (Interactable != nullptr)
		{
			return Actor;
		}
	}

	return nullptr;
}