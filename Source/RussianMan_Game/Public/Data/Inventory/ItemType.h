// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemType.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class RUSSIANMAN_GAME_API UItemType : public UObject
{
	GENERATED_BODY()

public:

	virtual void OnSelection(class ARussianCharacter* Caller) const {}
};
