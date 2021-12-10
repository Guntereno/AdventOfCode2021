#include "Counter.h"

#include "Components/TextRenderComponent.h"

// Sets default values
ACounter::ACounter():
	CurrentValue{ 0 }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACounter::BeginPlay()
{
	Super::BeginPlay();

	InitTextRender();
}

// Called every frame
void ACounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACounter::Reset()
{
	CurrentValue = 0;
	UpdateText();
}

void ACounter::Increment()
{
	++CurrentValue;
	UpdateText();
}

void ACounter::Set(int32 Value)
{
	CurrentValue = Value;
	UpdateText();
}

void ACounter::InitTextRender()
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

	UpdateText();
}

void ACounter::UpdateText()
{
	if (TextRender == nullptr)
	{
		return;
	}

	FString String = FString::Printf(TEXT("%d"), CurrentValue);
	TextRender->SetText(FText::FromString(String));
}
