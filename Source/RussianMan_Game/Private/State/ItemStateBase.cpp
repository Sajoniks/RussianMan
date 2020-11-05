// Fill out your copyright notice in the Description page of Project Settings.


#include "State/ItemStateBase.h"
#include "Actor/Inventory/InventoryItem.h"

AInventoryItem* UItemStateBase::GetStateOwner() const
{
	return GetTypedOuter<AInventoryItem>();
}

UWorld* UItemStateBase::GetWorld() const
{
	return GetStateOwner()->GetWorld();
}
