

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitPushButton(class APushButton* PushButton, FName CallbackName);
	void InitTerminal(class ATerminal* Terminal);
	void InitCounter(class ACounter* Counter);

	static FString GetAssetPath(const TCHAR* Path);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
