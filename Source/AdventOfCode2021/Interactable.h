#pragma once

#include "Interactable.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactions")
		void Interact();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactions")
		void StopInteracting();
};
