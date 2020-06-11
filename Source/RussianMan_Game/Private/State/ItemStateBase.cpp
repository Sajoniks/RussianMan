// Fill out your copyright notice in the Description page of Project Settings.


#include "State/ItemStateBase.h"
#include "State/StateMachine/StateMachine.h"

/*AInventoryItem* UItemStateBase::GetStateOwner() const
{
	return GetTypedOuter<AInventoryItem>();
}*/

UStateMachine* UItemStateBase::GetStateMachine() const
{
	return GetTypedOuter<UStateMachine>();
}

UWorld* UItemStateBase::GetWorld() const
{
	return nullptr;
}
