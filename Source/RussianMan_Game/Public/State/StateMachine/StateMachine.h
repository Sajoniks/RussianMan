// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachine.generated.h"

class UItemStateBase;

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

	virtual bool HandleInput();
	
	UItemStateBase* GetCurrentState() const;

	void PopState();
	void PushState(UItemStateBase* State);

	virtual void GotoState();
};
