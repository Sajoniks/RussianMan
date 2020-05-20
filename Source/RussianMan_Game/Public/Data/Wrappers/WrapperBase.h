// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/ItemStack.h"
#include "WrapperBase.generated.h"

struct FItemStack;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class RUSSIANMAN_GAME_API UWrapperBase : public UObject
{
	GENERATED_BODY()

	//Pointer to wrapped stack
	FItemStack* WrapStack;

	/**Clears containing stack (sets to null)
	 * @note Should be called at the end of Unwrap function, after calling of it, function GetStack() mustn't be called!!
	 */
	UFUNCTION(BlueprintCallable, Category="Interaction|Pickup|Utility")
	void ClearStackReference();

	/**Return containing stack reference
	 * @param Wrapped stack
	 * @note Mustn't be called after ClearStackReference() function call!!
	 */
	UFUNCTION(BlueprintCallable, Category="Interaction|Pickup|Utility")
	void GetStack(FItemStack& Stack) const;
	
public:

	/**Calls corresponding to stack function (eg. add weapon for weapons)
	 * @param Caller Where to add stack
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Interaction|Pickup|Wrapper")
	bool Unwrap(class ARussianCharacter* Caller);

	//Sets wrapper stack to this wrapper
	void SetStack(FItemStack& Stack);
};