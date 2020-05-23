// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachine.generated.h"

class UItemStateBase;

enum class EItemState : uint8
{
	Hidden,
	Active,
	Equipping,
	Unequipping,
	Reloading,
	Shooting,
	Charging,
	Aiming
};

/**
 * 
 */
UCLASS()
class RUSSIANMAN_GAME_API UStateMachine : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UItemStateBase*> StateStack;
	
public:

	UItemStateBase* GetCurrentState() const;

	void PopState();
	void PushState(EItemState State);
};
