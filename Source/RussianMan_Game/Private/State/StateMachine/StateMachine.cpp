// Fill out your copyright notice in the Description page of Project Settings.


#include "State/StateMachine/StateMachine.h"

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

void UStateMachine::GotoState()
{
}

bool UStateMachine::HandleInput()
{
	return false;
}

UItemStateBase* UStateMachine::GetCurrentState() const
{
	return StateStack.Top();
}
