// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InventoryComponent.h"
#include "PlayerInventoryComponent.generated.h"

/**
 * 
 */
UCLASS()
class RUSSIANMAN_GAME_API UPlayerInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()

	FGameplayTag ContainerID;

	float MaxWeight;
	uint32 MaxNum;

	bool AddStack_Impl(FItemStack& Stack) override;

	//Get amount of items that can be taken to inventory
	uint32 StripStack(const FItemStack& Stack) const;

public:

	UPlayerInventoryComponent();
	
	bool SetContainer(FItemStack& NewContainer);
};
