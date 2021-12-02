// Fill out your copyright notice in the Description page of Project Settings.


#include "AocCharacter.h"

// Sets default values
AAocCharacter::AAocCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAocCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("I'M HERE!"));
	
}

// Called every frame
void AAocCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
