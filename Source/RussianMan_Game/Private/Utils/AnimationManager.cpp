// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/AnimationManager.h"
#include "Interface/Animatable.h"
#include "RussianGameInstance.h"
#include "Data/ItemsRegistry.h"

void UAnimationManager::PlayAnimation(IAnimatable* Object, const FName& AnimationName)
{
	if (Object && !AnimationName.IsNone() && AnimationName.IsValid())
	{
		Object->PlayAnimation(AnimationName);
	}
}

FAnimationSet* UAnimationManager::GetAnimationsForItem(const FItemStack& Item)
{
	if (Item.IsValid() && URussianGameInstance::GetItemRegistry())
	{
		return URussianGameInstance::GetItemRegistry()->GetAnimationSet(Item.ID);
	}

	return nullptr;
}
