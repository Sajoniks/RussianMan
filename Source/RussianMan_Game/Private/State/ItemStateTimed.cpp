// Fill out your copyright notice in the Description page of Project Settings.


#include "State/ItemStateTimed.h"
#include "TimerManager.h"
#include "Actor/Inventory/InventoryItem.h"

UItemStateTimed::UItemStateTimed(const FObjectInitializer& ObjectInitializer)
{
	if (GetStateOwner())
		TimerManager = &GetStateOwner()->GetWorldTimerManager();
}

bool UItemStateTimed::IsStateFinished() const
{
	return Manager().IsTimerActive(TimerHandle);
}

float UItemStateTimed::GetStateDuration() const
{
	return GetStateOwner()->GetAnimationDuration(AnimationSectionName);
}

float UItemStateTimed::GetStateTimeRemaining() const
{
	return Manager().GetTimerRemaining(TimerHandle);
}
