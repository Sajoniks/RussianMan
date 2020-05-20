// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "ItemStack.h"

#include "ItemsRegistry.generated.h"

USTRUCT()
struct FItem
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="Data")
	TSoftObjectPtr<class UStaticMesh> WorldMesh;
};

/**
 * 
 */
UCLASS(Blueprintable)
class RUSSIANMAN_GAME_API UItemsRegistry : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	TMap<FGameplayTag, FItem> Items;
	
public:

	UStaticMesh* GetWorldMesh(const FGameplayTag& ID) const;
	FItemStack MakeStackFromID(const FGameplayTag& ID) const;
};
