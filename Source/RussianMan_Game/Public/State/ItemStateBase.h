// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemStateBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class RUSSIANMAN_GAME_API UItemStateBase : public UObject
{
	GENERATED_BODY()

public:

	virtual bool HandleInput() const { return false; }

	virtual void BeginState() {}

	virtual bool EndState() { return true; }

	virtual void HandleEvent() {}

	virtual void StateFinished() {}

	virtual bool IsStateFinished() const { return true; }

	virtual float GetStateDuration() const { return 0.f; }

	virtual float GetStateTimeRemaining() const { return 0.f; }

	virtual float GetStateTimeElapsed() const { return FMath::Abs(GetStateDuration() - GetStateTimeRemaining()); }

	//class AInventoryItem* GetStateOwner() const;
	class UStateMachine* GetStateMachine() const;
	class UWorld* GetWorld() const override;
};
