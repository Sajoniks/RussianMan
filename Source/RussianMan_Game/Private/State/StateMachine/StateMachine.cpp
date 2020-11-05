// Fill out your copyright notice in the Description page of Project Settings.


#include "State/StateMachine/StateMachine.h"
#include "Actor/Inventory/InventoryItem.h"

#include "State/States.h"

void UStateMachine::PopState()
{
	if (StateStack.Num() > 0)
		StateStack.Pop();
}

void UStateMachine::PushState(UItemStateBase* State)
{
	if (State)
		StateStack.Push(State);
}

void UStateMachine::GotoState(UItemStateBase* State)
{

}

AInventoryItem* UStateMachine::GetMachineOwner() const
{
	return GetTypedOuter<AInventoryItem>();
}

UStateMachine::UStateMachine(const FObjectInitializer& ObjectInitializer)
{
	UObject* Outer = GetOuter();
	
	StateHidden = ObjectInitializer.CreateDefaultSubobject<UItemStateInactive>(Outer, "State_Inactive");
	StateActive = ObjectInitializer.CreateDefaultSubobject<UItemStateActive>(Outer, "State_Active");
	StateEquip = ObjectInitializer.CreateDefaultSubobject<UItemStateInactive>(Outer, "State_Equip");
	StateHide = ObjectInitializer.CreateDefaultSubobject<UItemStateInactive>(Outer, "State_Hide");
}

bool UStateMachine::HandleInput()
{
	return false;
}

UItemStateBase* UStateMachine::GetCurrentState() const
{
	return StateStack.Top();
}
