// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Wrappers/WrapperBase.h"

void UWrapperBase::ClearStackReference()
{
	*WrapStack = FItemStack::EmptyStack;
	WrapStack = nullptr;
}

FItemStack& UWrapperBase::GetStack() const
{
	return *WrapStack;
}

void UWrapperBase::SetStack(FItemStack& Stack)
{
	WrapStack = &Stack;
}
