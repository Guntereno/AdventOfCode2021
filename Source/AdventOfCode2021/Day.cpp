#include "Day.h"

#include "PushButton.h"
#include "Counter.h"
#include "Terminal.h"

// Sets default values
ADay::ADay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADay::BeginPlay()
{
	Super::BeginPlay();

	InitPushButtons();
	InitTerminal();
	InitCounter();
}

// Called every frame
void ADay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ADay::InitPushButton(APushButton* PushButton, FName CallbackName)
{
	if (PushButton == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor '%s' has a null PushButton!"), *(GetName()));
		return;
	}

	PushButton->ButtonPushed.BindUFunction(this, CallbackName);
}


void ADay::InitPushButtons()
{
	InitPushButton(Part01TestButton, FName(TEXT("OnPart01TestButtonPushed")));
	InitPushButton(Part01Button, FName(TEXT("OnPart01ButtonPushed")));
	InitPushButton(Part02TestButton, FName(TEXT("OnPart02TestButtonPushed")));
	InitPushButton(Part02Button, FName(TEXT("OnPart02ButtonPushed")));
}


void ADay::InitTerminal()
{
	if (Terminal == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor '%s' has a null Terminal!"), *(GetName()));
		return;
	}

	Terminal->Clear();
}

void ADay::InitCounter()
{
	if (Counter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor '%s' has a null Counter!"), *(GetName()));
		return;
	}

	Counter->Reset();
}

FString ADay::GetAssetPath(const TCHAR* Path)
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() / Path);
}