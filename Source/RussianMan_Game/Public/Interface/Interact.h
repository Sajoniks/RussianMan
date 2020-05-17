// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interact.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
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

	virtual bool Interact() = 0;
	virtual void DrawToCustomDepth(bool bDraw);
};
