

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

private:
	void InitPushButtons();

	static EDay02Instruction ParseInstruction(const FName& InstructionName);
	static const TCHAR* InstructionToName(EDay02Instruction Instruction);
	static FDay02Command ParseLine(const FString& Line);
	static TArray<FDay02Command> LoadProgram(const TCHAR* FilePath);

	static void RunCommandPart01(const FDay02Command& Command, FIntPoint& Point);
	static void RunCommandPart02(const FDay02Command& Command, FIntPoint& Point, int32& Aim);
	
	bool InitTest();
	void RunTestPart01(const TArray<FDay02Command>& Program);
	void RunTestPart02(const TArray<FDay02Command>& Program);

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

	UPROPERTY()
		TArray<FDay02Command> SampleProgram;

	UPROPERTY()
		TArray<FDay02Command> InputProgram;
};
