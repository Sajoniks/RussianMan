// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemsRegistry.h"
#include "Data/Wrappers/WrapperBase.h"

UStaticMesh* UItemsRegistry::GetWorldMesh(const FGameplayTag& ID) const
{
	if (Items.Contains(ID))
		return Items[ID].WorldMesh.LoadSynchronous();

	return nullptr;
}

UWrapperBase* UItemsRegistry::GetWrapper(const FGameplayTag& ID) const
{
	if (Items.Contains(ID))
		return Items[ID].PickupWrapper.GetDefaultObject();

	return nullptr;
}

FItemStack UItemsRegistry::MakeStackFromID(const FGameplayTag& ID) const
{
	if (Items.Contains(ID))
	{
		FItemStack Stack{ ID, 1 };

		Stack.ScalarParameters = Items[ID].ScalarParameters;
		Stack.TagParameters = Items[ID].TaggedParameters;

		FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag("Param.Item.Weight");
		if (Stack.ScalarParameters.Contains(Tag))
			Stack.ItemWeight = Stack.ScalarParameters[Tag];

		Tag = UGameplayTagsManager::Get().RequestGameplayTag("Param.Item.MaxNum");

		if (Stack.ScalarParameters.Contains(Tag))
			Stack.MaxNum = FMath::FloorToInt(Stack.ScalarParameters[Tag]);
		
		return Stack;
	}

	return FItemStack::EmptyStack;
}
