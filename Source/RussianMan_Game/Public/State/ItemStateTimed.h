// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/ItemStateBase.h"
#include "ItemStateTimed.generated.h"

/**
 * 
 */
UCLASS(CustomConstructor)
class RUSSIANMAN_GAME_API UItemStateTimed : public UItemStateBase
{
	GENERATED_BODY()

	//Timer manager
	const FTimerManager* TimerManager;
	
protected:

	//Handle for timed events
	struct FTimerHandle TimerHandle;

	//Animation name that will be searched in the owning item animation montage
	const FName AnimationSectionName{ NAME_None };

	//Get timer manager
	const FTimerManager& Manager() const { return *TimerManager; }

public:

	UItemStateTimed(const FObjectInitializer& ObjectInitializer);

	bool IsStateFinished() const override;
	float GetStateDuration() const override;
	float GetStateTimeRemaining() const override;
};
