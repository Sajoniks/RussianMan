// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AnimationManager.generated.h"

class	IAnimatable;
struct	FItemStack;
struct	FAnimationSet;

/**
 * 
 */
UCLASS()
class RUSSIANMAN_GAME_API UAnimationManager : public UObject
{
	GENERATED_BODY()

	public:

	static void PlayAnimation(IAnimatable* Object, const FName& AnimationName);
	static FAnimationSet* GetAnimationsForItem(const FItemStack& Item);
};
