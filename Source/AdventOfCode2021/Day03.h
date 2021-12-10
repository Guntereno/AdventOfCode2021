#pragma once

#include "CoreMinimal.h"
#include "Day.h"
#include "Day03.generated.h"

USTRUCT()
struct FDay03Input
{
	GENERATED_BODY()

	TArray<uint32> Values;
	uint32 BitCount;
};

UCLASS()
class ADVENTOFCODE2021_API ADay03 : public ADay
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADay03();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnPart01TestButtonPushed() override;
	void OnPart01ButtonPushed() override;
	void OnPart02TestButtonPushed() override;
	void OnPart02ButtonPushed() override;

private:
	static bool LoadInput(const TCHAR* FilePath, FDay03Input& OutResult);
	static bool ParseBinaryString(const FString& Input, uint32& OutResult, uint32& NumBits);

	using FilterCriteria = bool(*)(uint32, uint32);

	static bool OxygenGeneratorRatingCriteria(uint32 BitsSet, uint32 BitsNotSet)
	{
		return (BitsSet >= BitsNotSet);
	}

	static bool CarbonDioxideScrubberRatingCriteria(uint32 BitsSet, uint32 BitsNotSet)
	{
		return (BitsNotSet > BitsSet);
	}

	static TArray<uint32> FilterValues(
		const TArray<uint32>& Values,
		uint32 CurrentBit,
		FilterCriteria Criteria);

	void RunTestPart01(const FDay03Input& Input);
	void RunTestPart02(const FDay03Input& Input);

	uint32 CalculateRating(const FDay03Input& Input, FilterCriteria Criteria);

	UPROPERTY()
		FDay03Input SampleInput;
	UPROPERTY()
		FDay03Input PuzzleInput;
};
