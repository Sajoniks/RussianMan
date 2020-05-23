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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stack")
	FGameplayTag ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stack")
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

	/**Map of scalar parameters
	 * @note Such as item weight, etc.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stack")
	TMap<FGameplayTag, float> ScalarParameters;

	/**Map of tagged parameters
	 *@note Such as ammo type, etc.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stack")
	TMap<FGameplayTag, FGameplayTag> TagParameters;
	
private:

	//Cached weight item weight
	float ItemWeight;

	//Cached max count
	uint32 MaxNum;

public:

	//Get ref to parameter of Type type
	template <class Type>
	const Type& GetParameter(const FName& ParamTag) const;

	/**Get value of parameter
	 * @param ParamTag		Parameter tag
	 * @note	 Used when it is not possible to return ref to parameter value
	 */
	template <class Type>
	Type GetParameterValue(const FName& ParamTag) const;

	/** Set parameter of type Type
	 * @param ParamTag		Tag of parameter
	 * @param Value			Value of parameter ParamTag
	 */
	template <class Type>
	void SetParameter(const FName& ParamTag, const Type& Value);

	float Weight() const;
	int32 Max() const;
};
