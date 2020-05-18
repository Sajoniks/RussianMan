// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interact.generated.h"

class ARussianCharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInteract : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RUSSIANMAN_GAME_API IInteract
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction|Interface")
	bool Interact(ARussianCharacter* Caller);

	virtual bool Interact_Implementation(ARussianCharacter* Caller) = 0;
	virtual void DrawToCustomDepth(bool bDraw);
};
