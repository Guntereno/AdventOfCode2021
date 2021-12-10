#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "PushButton.generated.h"

UCLASS()
class ADVENTOFCODE2021_API APushButton : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APushButton();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactions")
		void Interact();
	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactions")
		void StopInteracting();
	virtual void StopInteracting_Implementation() override;

	DECLARE_DELEGATE(FButtonPushedDelegate)
	FButtonPushedDelegate ButtonPushed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitButtonCap();

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TickButtonCap(float DeltaTime);

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = Button,
		meta = (AllowPrivateAccess = "true"))
		float PushOffset;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = Button,
		meta = (AllowPrivateAccess = "true"))
		float ButtonPressSpeed;

	UPROPERTY()
		class USceneComponent* ButtonCap;

	FVector DefaultLocation;
	FVector PressedLocation;
	bool IsPressed;
};
