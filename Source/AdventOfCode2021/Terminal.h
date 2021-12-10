

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Terminal.generated.h"

UCLASS()
class ADVENTOFCODE2021_API ATerminal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATerminal();

	void PrintLine(const FString& Line);
	void Clear();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void InitTextRender();
	bool PrintLineInternal(FString& Line);
	void UpdateTextRender();

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = Terminal,
		meta = (AllowPrivateAccess = "true"))
		int32 MaxLines = 10;

	UPROPERTY()
		class UTextRenderComponent* TextRender;

	TArray<FString> Buffer;

	int32 NumLines;
};
