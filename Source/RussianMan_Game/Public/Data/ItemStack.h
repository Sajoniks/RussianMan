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

	//Get parameter of Type type
	template <class Type>
	const Type& GetParameter(const FGameplayTag& ParamTag) const;

	/** Set parameter of type Type
	 * @param ParamTag		Tag of parameter
	 * @param Value			Value of parameter ParamTag
	 */
	template <class Type>
	void SetParameter(const FGameplayTag& ParamTag, const Type& Value);
};
