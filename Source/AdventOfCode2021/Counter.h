#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Counter.generated.h"

UCLASS()
class ADVENTOFCODE2021_API ACounter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACounter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Reset();

	UFUNCTION()
		void Increment();

	UFUNCTION()
		void Set(int32 Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void InitTextRender();
	void UpdateText();

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadonly,
		Category = Counter,
		meta = (AllowPrivateAccess = "true"))
		class UTextRenderComponent* TextRender;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadonly,
		Category = Counter,
		meta = (AllowPrivateAccess = "true"))
		int32 CurrentValue;
};
