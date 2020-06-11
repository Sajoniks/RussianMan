// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Inventory/ItemType.h"
#include "MainWeapon.generated.h"

/**
 * 
 */
UCLASS()
class RUSSIANMAN_GAME_API UMainWeapon : public UItemType
{
	GENERATED_BODY()

public:

	void OnSelection(ARussianCharacter* Caller) const override;
};
