


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

	InitPushButtons();
	InitTerminal(Terminal);
	InitCounter(Counter);
}

void ADay01::OnPart01TestButtonPushed()
{
	const FString InputPath = GetAssetPath(TEXT("Data/Day01/Test.txt"));
	RunTestPart01(*InputPath);
}

void ADay01::OnPart01ButtonPushed()
{
	const FString InputPath = GetAssetPath(TEXT("Data/Day01/Part01.txt"));
	RunTestPart01(*InputPath);
}

void ADay01::OnPart02TestButtonPushed()
{
	const FString InputPath = GetAssetPath(TEXT("Data/Day01/Test.txt"));
	RunTestPart02(*InputPath);
}

void ADay01::OnPart02ButtonPushed()
{
	const FString InputPath = GetAssetPath(TEXT("Data/Day01/Part01.txt"));
	RunTestPart02(*InputPath);
}

void ADay01::InitPushButtons()
{
	InitPushButton(Part01TestButton, FName(TEXT("OnPart01TestButtonPushed")));
	InitPushButton(Part01Button, FName(TEXT("OnPart01ButtonPushed")));
	InitPushButton(Part02TestButton, FName(TEXT("OnPart02TestButtonPushed")));
	InitPushButton(Part02Button, FName(TEXT("OnPart02ButtonPushed")));
}

bool ADay01::InitTest(const TCHAR* FilePath, TArray<int32>& Values)
{
	if ((Terminal == nullptr) || (Counter == nullptr))
	{
		return false;
	}

	Terminal->Clear();
	Counter->Reset();

	UE_LOG(LogTemp, Warning, TEXT("Loading file '%s'."), FilePath);
	TArray<FString> Lines;
	FFileHelper::LoadFileToStringArray(Lines, FilePath);

	Values.Empty();
	for (int i = 0; i < Lines.Num(); ++i)
	{
		Values.Emplace(FCString::Atoi(*(Lines[i])));
	}

	return true;
}

void ADay01::RunTestPart01(const TCHAR* FilePath)
{
	TArray<int32> Values;
	bool bInitialised = InitTest(FilePath, Values);
	if (!bInitialised)
	{
		return;
	}

	int32 ValueCount = Values.Num();
	if (ValueCount <= 1)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read file '%s'!"), FilePath);
		return;
	}

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

void ADay01::RunTestPart02(const TCHAR* FilePath)
{
	TArray<int32> Values;
	bool bInitialised = InitTest(FilePath, Values);
	if (!bInitialised)
	{
		return;
	}

	int32 ValueCount = Values.Num();
	if (ValueCount <= 4)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read file '%s'!"), FilePath);
		return;
	}

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