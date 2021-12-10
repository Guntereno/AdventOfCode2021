#include "PushButton.h"

#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
APushButton::APushButton() :
	PushOffset{ 50.0f },
	ButtonPressSpeed{ 150.0f },
	IsPressed{ false }
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APushButton::BeginPlay()
{
	Super::BeginPlay();

	InitButtonCap();
}

void APushButton::InitButtonCap()
{
	TArray<USceneComponent*, FDefaultAllocator> SceneComponents;
	GetComponents<USceneComponent>(SceneComponents, false);
	for (USceneComponent* SceneComponent : SceneComponents)
	{
		if (SceneComponent->GetName() == TEXT("Cap"))
		{
			ButtonCap = SceneComponent;
		}
	}

	if (ButtonCap == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Object '%s' has a Push Button with no 'Cap' component!"), *(GetName()));
		return;
	}

	DefaultLocation = ButtonCap->GetRelativeLocation();
	PressedLocation = DefaultLocation - FVector(0.0f, 0.0f, PushOffset);
}

// Called every frame
void APushButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickButtonCap(DeltaTime);
}

void APushButton::TickButtonCap(float DeltaTime)
{
	if (ButtonCap == nullptr)
	{
		return;
	}

	FVector Target = IsPressed ? PressedLocation : DefaultLocation;
	ButtonCap->SetRelativeLocation(FMath::VInterpTo(
		ButtonCap->GetRelativeLocation(),
		Target,
		DeltaTime,
		ButtonPressSpeed));
}

void APushButton::Interact_Implementation()
{
	IsPressed = true;

	ButtonPushed.ExecuteIfBound();
}

void APushButton::StopInteracting_Implementation()
{
	IsPressed = false;
}
