// Fill out your copyright notice in the Description page of Project Settings.


#include "RussianGameInstance.h"

UItemsRegistry* URussianGameInstance::ItemsRegistry_ = nullptr;

UItemsRegistry* URussianGameInstance::GetItemsRegistry() const
{
	return ItemsRegistry;
}

UItemsRegistry* URussianGameInstance::GetItemRegistry()
{
	return ItemsRegistry_;
}

void URussianGameInstance::OnStart()
{
	//Some workaround for static members
	ItemsRegistry_ = ItemsRegistry;
}