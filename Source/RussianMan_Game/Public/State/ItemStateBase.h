// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemStateBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class RUSSIANMAN_GAME_API UItemStateBase : public UObject
{
	GENERATED_BODY()

public:

	virtual bool HandleInput() const = 0;
};
