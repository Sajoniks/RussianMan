// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "ItemStack.generated.h"

/**
 * 
 */
USTRUCT()
struct FItemStack
{
	friend class UItemsRegistry;
	
	GENERATED_BODY()

	FGameplayTag ID;
	uint32 Count;
	
private:
	
	TMap<FGameplayTag, float> ScalarParameters;
	TMap<FGameplayTag, FGameplayTag> TagParameters;

public:

	template <class Type>
	const Type& GetParameter(const FGameplayTag& ParamTag) const;

	template <class Type>
	void SetParameter(const FGameplayTag& ParamTag, const Type& Value);
};
