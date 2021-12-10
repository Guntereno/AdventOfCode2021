#pragma once

#include "CoreMinimal.h"
#include "Day.h"
#include "Day01.generated.h"

UCLASS()
class ADVENTOFCODE2021_API ADay01 : public ADay
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADay01();

protected:
	virtual void BeginPlay() override;

	void OnPart01TestButtonPushed() override;
	void OnPart01ButtonPushed() override;
	void OnPart02TestButtonPushed() override;
	void OnPart02ButtonPushed() override;

private:
	TArray<int32> SampleInput;
	TArray<int32> PuzzleInput;

	static TArray<int32> LoadInput(const TCHAR* FilePath);

	bool InitTest(const TCHAR* FilePath, TArray<int32>& Values);
	void RunTestPart01(const TArray<int32>& Values);
	void RunTestPart02(const TArray<int32>& Values);

	TArray<FString> Lines;
};
