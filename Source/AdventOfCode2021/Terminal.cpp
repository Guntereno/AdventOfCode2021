
#include "Terminal.h"

#include "Components/TextRenderComponent.h"

// Sets default values
ATerminal::ATerminal():
	TextRender{ nullptr },
	MaxLines{ 16 },
	NumLines{ 0 }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATerminal::BeginPlay()
{
	Super::BeginPlay();

	InitTextRender();
}

void ATerminal::InitTextRender()
{
	TArray<UTextRenderComponent*, FDefaultAllocator> SceneComponents;
	GetComponents<UTextRenderComponent>(SceneComponents, false);
	int32 FoundCount = SceneComponents.Num();
	if (FoundCount == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor '%s' is missing a TextRender component!"), *(GetName()));
		return;
	}
	else if (FoundCount > 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor '%s' has multiple TextRender components. Using first."), *(GetName()));
	}
	TextRender = SceneComponents[0];

	Clear();
}

// Called every frame
void ATerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATerminal::PrintLine(const FString& Line)
{
	FString LocalLine{ Line };
	bool bContinue = false;
	do
	{
		bContinue = PrintLineInternal(LocalLine);
	} while (bContinue);

	UpdateTextRender();
}

void ATerminal::Clear()
{
	Buffer.Empty();
	NumLines = 0;
	UpdateTextRender();
}

bool ATerminal::PrintLineInternal(FString& Line)
{
	int32 IndexOfNewline = -1;
	bool bLineSplit = false;
	FString Remaining;
	if (Line.FindChar('\n', IndexOfNewline))
	{
		Line.Split(
			TEXT("\n"),
			&Line,
			&Remaining,
			ESearchCase::CaseSensitive,
			ESearchDir::FromStart);
	}

	Buffer.Emplace(Line);
	++NumLines;

	
	while (NumLines > MaxLines)
	{
		int32 excess = NumLines - MaxLines;
		Buffer.RemoveAt(0, excess, false);
		NumLines = MaxLines;
	}

	if (bLineSplit)
	{
		Line = Remaining;
		return true;
	}

	return false;
}

void ATerminal::UpdateTextRender()
{
	if (TextRender == nullptr)
	{
		return;
	}

	FString AllText;
	for (FString Line : Buffer)
	{
		AllText += (Line + TEXT("\n"));
	}
	TextRender->SetText(FText::FromString(AllText));
}
