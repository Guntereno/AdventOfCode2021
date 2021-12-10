


#include "Day01.h"

#include "PushButton.h"
#include "Terminal.h"
#include "Counter.h"

#include "Misc/FileHelper.h"

// Sets default values
ADay01::ADay01():
	Super()
{
}

// Called when the game starts or when spawned
void ADay01::BeginPlay()
{
	Super::BeginPlay();

	SampleInput = LoadInput(TEXT("Data/Day01/Test.txt"));
	PuzzleInput = LoadInput(TEXT("Data/Day01/Part01.txt"));
}

void ADay01::OnPart01TestButtonPushed()
{
	RunTestPart01(SampleInput);
}

void ADay01::OnPart01ButtonPushed()
{
	RunTestPart01(PuzzleInput);
}

void ADay01::OnPart02TestButtonPushed()
{
	RunTestPart02(SampleInput);
}

void ADay01::OnPart02ButtonPushed()
{
	RunTestPart02(PuzzleInput);
}

TArray<int32> ADay01::LoadInput(const TCHAR* FilePath)
{
	FString FullPath = GetAssetPath(FilePath);
	UE_LOG(LogTemp, Display, TEXT("Loading file '%s'."), *FullPath);

	TArray<FString> Lines;
	FFileHelper::LoadFileToStringArray(Lines, *FullPath);

	TArray<int32> Values;
	Values.Empty();
	for (int i = 0; i < Lines.Num(); ++i)
	{
		Values.Emplace(FCString::Atoi(*(Lines[i])));
	}

	if (Values.Num() <= 4)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read file '%s'!"), FilePath);
	}

	return Values;
}

void ADay01::RunTestPart01(const TArray<int32>& Values)
{
	Terminal->Clear();
	Counter->Reset();

	int32 ValueCount = Values.Num();

	int32 CurrentEntry = 0;
	int32 PreviousValue = Values[0];
	Terminal->PrintLine(FString::Printf(TEXT("%d: %d"), CurrentEntry, Values[0]));

	for (int i = 1; i < ValueCount; ++i)
	{
		int32 CurrentValue = Values[i];
		if (CurrentValue > PreviousValue)
		{
			Counter->Increment();
		}
		Terminal->PrintLine(
			FString::Printf(
				TEXT("%d: %d (%d)"),
				CurrentEntry,
				CurrentValue,
				CurrentValue - PreviousValue));

		PreviousValue = CurrentValue;
	}
}

void ADay01::RunTestPart02(const TArray<int32>& Values)
{
	Terminal->Clear();
	Counter->Reset();

	int32 ValueCount = Values.Num();

	int32 CurrentEntry = 0;
	int32 Previous = Values[0] + Values[1] + Values[2];
	Terminal->PrintLine(
		FString::Printf(
			TEXT("%d: %d + %d + %d = %d"),
			CurrentEntry,
			Values[0], Values[1], Values[2],
			Previous));

	for (int i = 1; i < (ValueCount - 2); ++i)
	{
		++CurrentEntry;

		int32 Val1 = Values[i + 0];
		int32 Val2 = Values[i + 1];
		int32 Val3 = Values[i + 2];
		int32 Current = Val1 + Val2 + Val3;
		Terminal->PrintLine(
			FString::Printf(
				TEXT("%d: %d + %d + %d = %d (%d)"),
				CurrentEntry,
				Val1, Val2, Val3,
				Current,
				Current - Previous));

		if (Current > Previous)
		{
			Counter->Increment();
		}

		Previous = Current;
	}
}