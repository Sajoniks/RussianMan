// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemStack.h"

FItemStack FItemStack::EmptyStack;

template <>
int32 FItemStack::GetParameterValue(const FName& ParamTag) const
{
	const FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(ParamTag);
	return FMath::FloorToInt(ScalarParameters.FindRef(Tag));
}

template <>
const float& FItemStack::GetParameter(const FName& ParamTag) const
{
	const FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(ParamTag);
	return ScalarParameters.FindChecked(Tag);
}

template <>
const FGameplayTag& FItemStack::GetParameter(const FName& ParamTag) const
{
	const FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(ParamTag);
	return TagParameters.FindChecked(Tag);
}

template <>
void FItemStack::SetParameter(const FName& ParamTag, const float& Value)
{
	const FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(ParamTag);
	
	if (ScalarParameters.Contains(Tag))
		ScalarParameters[Tag] = Value;
}

template <>
void FItemStack::SetParameter(const FName& ParamTag, const FGameplayTag& Value)
{
	const FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(ParamTag);
	
	if (TagParameters.Contains(Tag))
		TagParameters[Tag] = Value;
}

bool FItemStack::IsValid() const
{
	return ID.IsValid() && Num > 0 && ItemWeight >= 0;
}

bool FItemStack::operator==(const FItemStack& ItemStack) const
{
	return (ItemStack.ID.MatchesTagExact(ID) || !ItemStack.ID.IsValid() && !ID.IsValid()) && Num == ItemStack.Num;
}

bool FItemStack::operator==(const FGameplayTag& ItemID) const
{
	return ItemID.MatchesTagExact(ID) || !ItemID.IsValid() && !ID.IsValid();
}

FItemStack::FItemStack(const FGameplayTag& ID, uint32 Num)
	: ID(ID), Num(Num), ItemWeight(-1), MaxNum(0)
{

}

FItemStack::FItemStack()
	: ID(FGameplayTag::EmptyTag), Num(0), ItemWeight(-1), MaxNum(0)
{
}

float FItemStack::Weight() const
{
	return ItemWeight * Num;
}

int32 FItemStack::Max() const
{
	return MaxNum;
}
