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
	int32 Num;

	//Check if stack is valid (ID is not null and Num is not zero)
	bool IsValid() const;

	/**Check stacks equality
	 *@param ItemStack Other stack to compare
	 */
	bool operator==(const FItemStack& ItemStack) const;

	/**Check stacks equality
	 *@param ItemID ID of item to compare
	 */
	bool operator==(const FGameplayTag& ItemID) const;

	//Empty stack
	static FItemStack EmptyStack;

	FItemStack(const FGameplayTag& ID, uint32 Num);
	FItemStack();
	
private:

	/**Map of scalar parameters
	 * @note Such as item weight, etc.
	 */
	TMap<FGameplayTag, float> ScalarParameters;

	/**Map of tagged parameters
	 *@note Such as ammo type, etc.
	 */
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
