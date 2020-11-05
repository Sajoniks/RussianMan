// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachine.generated.h"

class UItemStateBase;

enum class EState : uint8
{
	Hide,
	Equip,
	Active,
	Inactive
};

UCLASS(CustomConstructor)
class RUSSIANMAN_GAME_API UStateMachine : public UObject
{
	friend class UItemStateBase;
	
	GENERATED_BODY()

	UPROPERTY()
	TArray<UItemStateBase*> StateStack;

	void PushState(UItemStateBase* State);
	
public:
	
	UPROPERTY()
	class UItemStateBase* StateHidden;

	UPROPERTY()
	class UItemStateBase* StateEquip;

	UPROPERTY()
	class UItemStateBase* StateActive;

	UPROPERTY()
	class UItemStateBase* StateHide;

	
	UStateMachine(const FObjectInitializer& ObjectInitializer);
		
	virtual bool HandleInput();
	
	UItemStateBase* GetCurrentState() const;

	void PopState();

	virtual void GotoState(UItemStateBase* State);

	class AInventoryItem* GetMachineOwner() const;
};
