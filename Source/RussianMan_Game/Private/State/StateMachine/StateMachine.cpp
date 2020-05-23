// Fill out your copyright notice in the Description page of Project Settings.


#include "State/StateMachine/StateMachine.h"

void UStateMachine::PopState()
{
	if (StateStack.Num() > 0)
		StateStack.Pop();
}

UItemStateBase* UStateMachine::GetCurrentState() const
{
	return StateStack.Top();
}
