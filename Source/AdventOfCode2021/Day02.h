#pragma once

#include "CoreMinimal.h"
#include "Day.h"
#include "Day02.generated.h"

UENUM()
enum class EDay02Instruction : uint8
{
	Invalid = 0,
	Forward,
	Down,
	Up
};

USTRUCT()
struct FDay02Command
{
	GENERATED_BODY()

		EDay02Instruction Instruction;
	int32 Value;
};

UCLASS()
class ADVENTOFCODE2021_API ADay02 : public ADay
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADay02();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnPart01TestButtonPushed() override;
	void OnPart01ButtonPushed() override;
	void OnPart02TestButtonPushed() override;
	void OnPart02ButtonPushed() override;

private:
	static EDay02Instruction ParseInstruction(const FName& InstructionName);
	static const TCHAR* InstructionToName(EDay02Instruction Instruction);
	static FDay02Command ParseLine(const FString& Line);
	static TArray<FDay02Command> LoadProgram(const TCHAR* FilePath);

	static void RunCommandPart01(const FDay02Command& Command, FIntPoint& Point);
	static void RunCommandPart02(const FDay02Command& Command, FIntPoint& Point, int32& Aim);

	bool InitTest();
	void RunTestPart01(const TArray<FDay02Command>& Program);
	void RunTestPart02(const TArray<FDay02Command>& Program);

	UPROPERTY()
		TArray<FDay02Command> SampleProgram;

	UPROPERTY()
		TArray<FDay02Command> InputProgram;
};
