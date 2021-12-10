// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AocCharacter.generated.h"

UCLASS()
class ADVENTOFCODE2021_API AAocCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAocCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Yaw(float Value);
	void Pitch(float Value);
	void AddControllerYawInput(float Value);
	void AddControllerPitchInput(float Value);

	void Interact();
	void StopInteracting();
	void TickInteraction();

	void GetRay(FVector& Origin, FVector& Target) const;
	bool GetFirstActorInReach(FHitResult& HitResult) const;
	bool GetFirstActorInReach(
		const FVector& RayOrigin,
		const FVector& RayTarget,
		FHitResult& HitResult) const;
	AActor* GetFirstInteractableInReach() const;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = Camera,
		meta = (AllowPrivateAccess = "true"))
		float PitchRate; // Degrees per second

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = Camera,
		meta = (AllowPrivateAccess = "true"))
		float YawRate; // Degrees per second

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = Camera,
		meta = (AllowPrivateAccess = "true"))
		float Reach;

	UPROPERTY()
		class AActor* CurrentInteractable;
};
