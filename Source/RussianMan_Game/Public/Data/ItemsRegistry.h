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

	//Mesh of this item when it is spawned as pickup
	UPROPERTY(EditDefaultsOnly, Category="Data")
	TSoftObjectPtr<class UStaticMesh> WorldMesh;

	//Action that will be executed when this item is collected
	UPROPERTY(EditDefaultsOnly, Category="Data")
	TSubclassOf<class UWrapperBase> PickupWrapper;

	//Map of tagged scalar parameters (eg Param.Weight = 1.0)
	UPROPERTY(EditDefaultsOnly, Category="Data")
	TMap<FGameplayTag, float> ScalarParameters;

	//Map of tagged tag parameters (eg Param.AmmoType = Ammo.Machine)
	UPROPERTY(EditDefaultsOnly, Category="Data")
	TMap<FGameplayTag, FGameplayTag> TaggedParameters;
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

	UStaticMesh*		GetWorldMesh(const FGameplayTag& ID)		const;
	UWrapperBase*		GetWrapper(const FGameplayTag& ID)			const;
	
	FItemStack			MakeStackFromID(const FGameplayTag& ID)	const;
};
