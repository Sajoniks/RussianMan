// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Animatable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimatable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RUSSIANMAN_GAME_API IAnimatable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void	PlayAnimation(const FName& AnimationName)				 = 0;
	virtual float	GetAnimationDuration(const FName& AnimationName) const	 = 0;
};
