// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemsRegistry.h"

UStaticMesh* UItemsRegistry::GetWorldMesh(const FGameplayTag& ID) const
{
	if (Items.Contains(ID))
		return Items[ID].WorldMesh.LoadSynchronous();

	return nullptr;
}
