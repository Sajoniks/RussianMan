// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemStack.h"

FItemStack FItemStack::EmptyStack;

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
	if (ScalarParameters.Contains(ParamTag))
		ScalarParameters[ParamTag] = Value;
}

template <>
void FItemStack::SetParameter(const FGameplayTag& ParamTag, const FGameplayTag& Value)
{
	if (TagParameters.Contains(ParamTag))
		TagParameters[ParamTag] = Value;
}

bool FItemStack::IsValid() const
{
	return ID.IsValid() && Num > 0;
}

bool FItemStack::operator==(const FItemStack& ItemStack) const
{
	return ItemStack.ID.MatchesTagExact(ID) && Num == ItemStack.Num;
}

bool FItemStack::operator==(const FGameplayTag& ItemID) const
{
	return ItemID.MatchesTagExact(ID);
}

FItemStack::FItemStack(const FGameplayTag& ID, uint32 Num)
	:ID(ID), Num(Num)
{}

FItemStack::FItemStack()
	:ID(FGameplayTag::EmptyTag), Num(0) {}
