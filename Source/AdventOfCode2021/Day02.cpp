


#include "Day02.h"

#include "PushButton.h"
#include "Terminal.h"
#include "Counter.h"

#include "Misc/FileHelper.h"

// Sets default values
ADay02::ADay02() :
	Super()
{
}

// Called when the game starts or when spawned
void ADay02::BeginPlay()
{
	Super::BeginPlay();

	InitPushButtons();
	InitTerminal(Terminal);
	InitCounter(Counter);
}

void ADay02::OnPart01TestButtonPushed()
{
	const FString InputPath = GetAssetPath(TEXT("Data/Day02/Test01.txt"));
	RunTestPart01(*InputPath);
}

void ADay02::OnPart01ButtonPushed()
{
	const FString InputPath = GetAssetPath(TEXT("Data/Day02/Input01.txt"));
	RunTestPart01(*InputPath);
}

void ADay02::OnPart02TestButtonPushed()
{
	const FString InputPath = GetAssetPath(TEXT("Data/Day02/Test01.txt"));
	RunTestPart02(*InputPath);
}

void ADay02::OnPart02ButtonPushed()
{
	const FString InputPath = GetAssetPath(TEXT("Data/Day02/Input01.txt"));
	RunTestPart02(*InputPath);
}

void ADay02::InitPushButtons()
{
	InitPushButton(Part01TestButton, FName(TEXT("OnPart01TestButtonPushed")));
	InitPushButton(Part01Button, FName(TEXT("OnPart01ButtonPushed")));
	InitPushButton(Part02TestButton, FName(TEXT("OnPart02TestButtonPushed")));
	InitPushButton(Part02Button, FName(TEXT("OnPart02ButtonPushed")));
}

const TCHAR* ADay02::InstructionToName(EDay02Instruction Instruction)
{
	switch (Instruction)
	{
	case EDay02Instruction::Forward:
	{
		return TEXT("forward");
	}
	case EDay02Instruction::Down:
	{
		return TEXT("down");
	}
	case EDay02Instruction::Up:
	{
		return TEXT("up");
	}
	default:
		UE_LOG(
			LogTemp,
			Error,
			TEXT("Unhandled instruction '%d' found in program!"),
			Instruction);
		return nullptr;
	}
}

EDay02Instruction ADay02::ParseInstruction(const FName& InstructionName)
{
	const UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EDay02Instruction"), true);
	if (Enum != nullptr)
	{
		int32 Index = Enum->GetIndexByName(InstructionName);
		EDay02Instruction Instruction = EDay02Instruction((uint8)Index);
		return Instruction;
	}

	UE_LOG(
		LogTemp,
		Error,
		TEXT("Failed to find instruction with name '%s'!"),
		*(InstructionName.ToString()));
	return EDay02Instruction{};
}

FDay02Command ADay02::ParseLine(const FString& Line)
{
	FString Left, Right;
	Line.Split(
		FString(TEXT(" ")),
		&Left,
		&Right,
		ESearchCase::CaseSensitive,
		ESearchDir::FromStart);

	EDay02Instruction Instruction = ParseInstruction(FName(Left));
	int32 Value = FCString::Atoi(*Right);
	return FDay02Command{ Instruction, Value };
}

TArray<FDay02Command> ADay02::LoadProgram(const TCHAR* FilePath)
{
	UE_LOG(LogTemp, Warning, TEXT("Loading file '%s'."), FilePath);
	TArray<FString> Lines;
	FFileHelper::LoadFileToStringArray(Lines, FilePath);

	TArray<FDay02Command> Program;
	for (FString Line : Lines)
	{
		Program.Emplace(ParseLine(Line));
	}

	return Program;
}

void ADay02::RunCommandPart01(const FDay02Command& Command, FIntPoint& Point)
{
	switch (Command.Instruction)
	{
	case EDay02Instruction::Forward:
	{
		Point.X += Command.Value;
		break;
	}
	case EDay02Instruction::Down:
	{
		Point.Y += Command.Value;
		break;
	}
	case EDay02Instruction::Up:
	{
		Point.Y -= Command.Value;
		break;
	}
	default:
		UE_LOG(
			LogTemp,
			Error,
			TEXT("Unhandled instruction '%d' found in program!"),
			Command.Instruction);
		break;
	}
}

void ADay02::RunCommandPart02(const FDay02Command& Command, FIntPoint& Point, int32& Aim)
{
	switch (Command.Instruction)
	{
	case EDay02Instruction::Forward:
	{
		Point.X += Command.Value;
		Point.Y += Aim * Command.Value;
		break;
	}
	case EDay02Instruction::Down:
	{
		Aim += Command.Value;
		break;
	}
	case EDay02Instruction::Up:
	{
		Aim -= Command.Value;
		break;
	}
	default:
		UE_LOG(
			LogTemp,
			Error,
			TEXT("Unhandled instruction '%d' found in program!"),
			Command.Instruction);
		break;
	}
}

bool ADay02::InitTest(const TCHAR* FilePath, TArray<FDay02Command>& Program)
{
	if ((Terminal == nullptr) || (Counter == nullptr))
	{
		return false;
	}

	Terminal->Clear();
	Counter->Reset();

	Program = LoadProgram(FilePath);

	return true;
}

void ADay02::RunTestPart01(const TCHAR* FilePath)
{
	TArray<FDay02Command> Program;
	if (!InitTest(FilePath, Program))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load program at '%s'!"), FilePath);
		return;
	}

	FIntPoint Pos{ 0, 0 };
	for (FDay02Command Command : Program)
	{
		RunCommandPart01(Command, Pos);

		Terminal->PrintLine(
			FString::Printf(
				TEXT("%s %d: Pos=(%d, %d)"),
				InstructionToName(Command.Instruction),
				Command.Value,
				Pos.X,
				Pos.Y));
	}

	Counter->Set(Pos.X * Pos.Y);
}

void ADay02::RunTestPart02(const TCHAR* FilePath)
{
	TArray<FDay02Command> Program;
	if (!InitTest(FilePath, Program))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load program at '%s'!"), FilePath);
		return;
	}

	FIntPoint Pos{ 0, 0 };
	int32 Aim{ 0 };
	for (FDay02Command Command : Program)
	{
		RunCommandPart02(Command, Pos, Aim);

		Terminal->PrintLine(
			FString::Printf(
				TEXT("%s %d: Pos=(%d, %d), Aim=%d"),
				InstructionToName(Command.Instruction),
				Command.Value,
				Pos.X,
				Pos.Y,
				Aim));
	}

	Counter->Set(Pos.X * Pos.Y);
}