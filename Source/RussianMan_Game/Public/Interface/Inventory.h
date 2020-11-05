// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inventory.generated.h"

enum class EInventoryType : uint8
{
	PlayerInventory,
	ContainerInventory
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventory : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RUSSIANMAN_GAME_API IInventory
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual class UInventoryComponent* GetInventory() const = 0;
	virtual EInventoryType GetInventoryType() const = 0;
};
