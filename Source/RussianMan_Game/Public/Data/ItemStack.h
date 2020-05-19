// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "ItemStack.generated.h"

/** Represents item in inventory
 * 
 */
USTRUCT(BlueprintType)
struct RUSSIANMAN_GAME_API FItemStack
{
	friend class UItemsRegistry;
	
	GENERATED_BODY()

	FGameplayTag ID;
	uint32 Num;
	
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

template <class Type>
const Type& FItemStack::GetParameter(const FGameplayTag& ParamTag) const
{
	check("No implementation for given template type!");
	return static_cast<Type>(0.f);
}

template <class Type>
void FItemStack::SetParameter(const FGameplayTag& ParamTag, const Type& Value)
{
	check("No implementation for given template type!");
}
