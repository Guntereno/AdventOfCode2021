

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

private:
	void InitPushButtons();

	bool InitTest(const TCHAR* FilePath, TArray<int32>& Values);
	void RunTestPart01(const TCHAR* FilePath);
	void RunTestPart02(const TCHAR* FilePath);

	UFUNCTION()
		void OnPart01TestButtonPushed();

	UFUNCTION()
		void OnPart01ButtonPushed();

	UFUNCTION()
		void OnPart02TestButtonPushed();

	UFUNCTION()
		void OnPart02ButtonPushed();

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
};
