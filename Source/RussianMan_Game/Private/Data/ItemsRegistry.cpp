// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemsRegistry.h"
#include "Data/Inventory/ItemType.h"
#include "Data/Wrappers/WrapperBase.h"
#include "State/StateMachine/StateMachine.h"

UStaticMesh* UItemsRegistry::GetWorldMesh(const FGameplayTag& ID) const
{
	if (Items.Contains(ID))
		return Items[ID].WorldMesh.LoadSynchronous();

	return nullptr;
}

USkeletalMesh* UItemsRegistry::GetViewportMesh(const FGameplayTag& ID) const
{
	if (Items.Contains(ID))
		return Items[ID].ViewportMesh.LoadSynchronous();

	return nullptr;
}

UItemType* UItemsRegistry::GetItemType(const FGameplayTag& ID) const
{
	if (Items.Contains(ID))
		return Items[ID].ItemType.GetDefaultObject();

	return nullptr;
}

UWrapperBase* UItemsRegistry::GetWrapper(const FGameplayTag& ID) const
{
	if (Items.Contains(ID))
		return Items[ID].PickupWrapper.GetDefaultObject();

	return nullptr;
}

UStateMachine* UItemsRegistry::GetStateMachine(const FGameplayTag& ID) const
{
	if (Items.Contains(ID))
		return Items[ID].StateMachine.GetDefaultObject();

	return nullptr;
}

FAnimationSet* UItemsRegistry::GetAnimationSet(const FGameplayTag& ID)
{
	if (Items.Contains(ID))
		return &Items[ID].AnimationSet;

	return nullptr;
}

FItemStack UItemsRegistry::MakeStackFromID(const FGameplayTag& ID) const
{
	if (Items.Contains(ID))
	{
		FItemStack Stack{ ID, 1 };

		Stack.ScalarParameters = Items[ID].ScalarParameters;
		Stack.TagParameters = Items[ID].TaggedParameters;

		Stack.MaxNum = Stack.GetParameterValue<int32>("Param.Item.MaxNum");
		Stack.ItemWeight = Stack.GetParameter<float>("Param.Item.Weight");
		
		return Stack;
	}

	return FItemStack::EmptyStack;
}
