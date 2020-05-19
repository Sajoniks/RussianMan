// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemStack.h"

template <>
const float& FItemStack::GetParameter(const FGameplayTag& ParamTag) const
{
	check(ScalarParameters.Contains(ParamTag));
	return ScalarParameters[ParamTag];
}

template <>
const FGameplayTag& FItemStack::GetParameter(const FGameplayTag& ParamTag) const
{
	check(TagParameters.Contains(ParamTag))
	return TagParameters[ParamTag];
}

template <>
void FItemStack::SetParameter(const FGameplayTag& ParamTag, const float& Value)
{
	
}

template <>
void FItemStack::SetParameter(const FGameplayTag& ParamTag, const FGameplayTag& Value)
{
	
}