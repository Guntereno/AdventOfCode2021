#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Day.generated.h"

UCLASS()
class ADVENTOFCODE2021_API ADay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADay();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	static FString GetAssetPath(const TCHAR* Path);

	UFUNCTION()
		virtual void OnPart01TestButtonPushed() {};

	UFUNCTION()
		virtual void OnPart01ButtonPushed() {};

	UFUNCTION()
		virtual void OnPart02TestButtonPushed() {};

	UFUNCTION()
		virtual void OnPart02ButtonPushed() {};

	UPROPERTY(
		EditAnyWhere,
		BlueprintReadWrite,
		Category = Puzzle,
		meta = (AllowPrivateAccess = "true"))
		class APushButton* Part01TestButton;

	UPROPERTY(
		EditAnyWhere,
		BlueprintReadWrite,
		Category = Puzzle,
		meta = (AllowPrivateAccess = "true"))
		class APushButton* Part01Button;

	UPROPERTY(
		EditAnyWhere,
		BlueprintReadWrite,
		Category = Puzzle,
		meta = (AllowPrivateAccess = "true"))
		class APushButton* Part02TestButton;

	UPROPERTY(
		EditAnyWhere,
		BlueprintReadWrite,
		Category = Puzzle,
		meta = (AllowPrivateAccess = "true"))
		class APushButton* Part02Button;

	UPROPERTY(
		EditAnyWhere,
		BlueprintReadWrite,
		Category = Puzzle,
		meta = (AllowPrivateAccess = "true"))
		class ATerminal* Terminal;

	UPROPERTY(
		EditAnyWhere,
		BlueprintReadWrite,
		Category = Puzzle,
		meta = (AllowPrivateAccess = "true"))
		class ACounter* Counter;

private:
	void InitPushButtons();

	void InitPushButton(class APushButton* PushButton, FName CallbackName);
	void InitTerminal();
	void InitCounter();
};
