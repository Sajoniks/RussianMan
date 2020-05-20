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

public:

	bool SetContainer(FItemStack& NewContainer);
	
	void AddStack(FItemStack& Stack) override;

};
