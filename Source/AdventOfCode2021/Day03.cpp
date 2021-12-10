#include "Day03.h"

#include "Terminal.h"
#include "Counter.h"

// Sets default values
ADay03::ADay03()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADay03::BeginPlay()
{
	Super::BeginPlay();

	LoadInput(TEXT("Data/Day03/Sample01.txt"), SampleInput);
	LoadInput(TEXT("Data/Day03/Input01.txt"), PuzzleInput);
}

// Called every frame
void ADay03::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADay03::OnPart01TestButtonPushed()
{
	RunTestPart01(SampleInput);
}

void ADay03::OnPart01ButtonPushed()
{
	RunTestPart01(PuzzleInput);
}

void ADay03::OnPart02TestButtonPushed()
{
	RunTestPart02(SampleInput);
}

void ADay03::OnPart02ButtonPushed()
{
	RunTestPart02(PuzzleInput);
}


bool ADay03::LoadInput(const TCHAR* FilePath, FDay03Input& OutResult)
{
	FString FullPath = GetAssetPath(FilePath);
	UE_LOG(LogTemp, Display, TEXT("Loading file '%s'."), *FullPath);

	TArray<FString> Lines;
	bool bSuccess = FFileHelper::LoadFileToStringArray(Lines, *FullPath);
	if (!bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to open file '%s'!"), *FullPath);
		return false;
	}

	OutResult.Values.Empty();
	OutResult.BitCount = 0;
	for (FString Line : Lines)
	{
		uint32 Value;
		uint32 BitCount;
		bSuccess = ParseBinaryString(Line, Value, BitCount);
		if (!bSuccess)
		{
			return false;
		}

		if (BitCount > OutResult.BitCount)
		{
			OutResult.BitCount = BitCount;
		}

		OutResult.Values.Emplace(Value);
	}

	return true;
}

bool ADay03::ParseBinaryString(const FString& Input, uint32& OutResult, uint32& NumBits)
{
	OutResult = 0;

	NumBits = Input.Len();
	for (uint32 Index = 0; Index < NumBits; ++Index)
	{
		int32 CharIndex = (NumBits - 1) - Index;
		TCHAR Char = Input[CharIndex];
		switch (Char)
		{
		case '1':
		{
			OutResult |= (1 << Index);
			break;
		}
		case '0':
		{
			// Do nothing
			break;
		}
		default:
		{
			UE_LOG(
				LogTemp,
				Error,
				TEXT("Invalid character '%c' found in input!"), Char);
			return false;
		}
		}
	}

	return true;
}

void ADay03::RunTestPart01(const FDay03Input& Input)
{
	int32 NumValues = Input.Values.Num();

	TArray<uint32> BitCounts;
	BitCounts.SetNum(Input.BitCount);

	uint32 Mask = 0;
	for (uint32 BitIndex = 0; BitIndex < Input.BitCount; ++BitIndex)
	{
		Mask |= (1 << BitIndex);
	}

	for (int32 InputIndex = 0; InputIndex < NumValues; ++InputIndex)
	{
		uint32 Value = Input.Values[InputIndex];
		for (uint32 BitIndex = 0; BitIndex < Input.BitCount; BitIndex++)
		{
			if (((1 << BitIndex) & Value) != 0)
			{
				BitCounts[BitIndex]++;
			}
		}
	}

	uint32 GammaRate{ 0 };
	uint32 HighestMinority = NumValues / 2;
	for (uint32 BitIndex = 0; BitIndex < Input.BitCount; BitIndex++)
	{
		if (BitCounts[BitIndex] > HighestMinority)
		{
			GammaRate |= (1 << BitIndex);
		}
	}

	uint32 EpsilonRate{ ((uint32)~GammaRate) & Mask };

	Terminal->Clear();

	for (uint32 BitIndex = 0; BitIndex < Input.BitCount; BitIndex++)
	{
		Terminal->PrintLine(FString::Printf(TEXT("Bit %d: %d set"), BitIndex, BitCounts[BitIndex]));
	}

	Terminal->PrintLine(FString::Printf(TEXT("Gamma Rate=%d"), GammaRate));
	Terminal->PrintLine(FString::Printf(TEXT("Epsilon Rate=%d"), EpsilonRate));
	Counter->Set(GammaRate * EpsilonRate);
}


void ADay03::RunTestPart02(const FDay03Input& Input)
{
	Terminal->Clear();

	uint32 OxygenGeneratorRating = CalculateRating(Input, OxygenGeneratorRatingCriteria);
	Terminal->PrintLine(
		FString::Printf(
			TEXT("Oxygen Generator Rating = %d"),
			OxygenGeneratorRating));
	
	uint32 CarbonDioxideScrubberRating = CalculateRating(Input, CarbonDioxideScrubberRatingCriteria);
	Terminal->PrintLine(
		FString::Printf(
			TEXT("Carbon Dioxide Scrubber Rating = %d"),
			CarbonDioxideScrubberRating));

	Counter->Set(OxygenGeneratorRating * CarbonDioxideScrubberRating);
}

uint32 ADay03::CalculateRating(const FDay03Input& Input, FilterCriteria Criteria)
{
	TArray<uint32> CurrentFilter = Input.Values;
	for (
		uint32 BitIndex = (Input.BitCount - 1);
		BitIndex >= 0;
		--BitIndex)
	{
		TArray<uint32> NextFilter = FilterValues(CurrentFilter, BitIndex, Criteria);
		if (NextFilter.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Error filtering values!"));
			return -1;
		}
		else if (NextFilter.Num() == 1)
		{
			return NextFilter[0];
		}
		CurrentFilter = NextFilter;
	}

	UE_LOG(LogTemp, Error, TEXT("Error filtering values!"));
	return -1;
}

TArray<uint32> ADay03::FilterValues(
	const TArray<uint32>& Values,
	uint32 CurrentBit,
	FilterCriteria Criteria)
{
	uint32 BitsSet = 0;
	uint32 Mask = 1 << CurrentBit;
	for (uint32 Value : Values)
	{
		if ((Value & Mask) != 0)
		{
			++BitsSet;
		}
	}

	uint32 TestValue = 0;
	uint32 BitsNotSet = (Values.Num() - BitsSet);
	if (Criteria(BitsSet, BitsNotSet))
	{
		TestValue = Mask;
	}

	TArray<uint32> Result;
	for (uint32 Value : Values)
	{
		if ((Value & Mask) == TestValue)
		{
			Result.Emplace(Value);
		}
	}

	return Result;
}