// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Wrappers/WrapperBase.h"

void UWrapperBase::ClearStackReference()
{
	*WrapStack = FItemStack::EmptyStack;
	WrapStack = nullptr;
}

void UWrapperBase::GetStack(FItemStack& Stack) const
{
	Stack = *WrapStack;
}

void UWrapperBase::SetStack(FItemStack& Stack)
{
	WrapStack = &Stack;
}
