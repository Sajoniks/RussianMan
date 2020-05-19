// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemStack.h"

template <>
const float& FItemStack::GetParameter(const FGameplayTag& ParamTag) const
{

}

template <>
const FGameplayTag& GetParameter(const FGameplayTag& ParamTag) const
{
	
}

template <>
void SetParameter(const FGameplayTag& ParamTag, const float& Value)
{
	
}

template <>
void SetParameter(const FGameplayTag& ParamTag, const FGameplayTag& Value)
{
	
}