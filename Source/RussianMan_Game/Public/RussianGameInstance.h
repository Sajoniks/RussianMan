// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RussianGameInstance.generated.h"

class UItemsRegistry;

/**
 * 
 */
UCLASS(Blueprintable)
class RUSSIANMAN_GAME_API URussianGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Registry|Items")
	UItemsRegistry* ItemsRegistry;

	static UItemsRegistry* ItemsRegistry_;

public:

	UFUNCTION(BlueprintCallable, Category="Registry|Get")
	UItemsRegistry* GetItemsRegistry() const;

	static UItemsRegistry* GetItemRegistry();

	void OnStart() override;
};
