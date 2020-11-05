// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Animatable.h"
#include "InventoryItem.generated.h"

struct FItemStack;
class UItemStateBase;

UCLASS()
class RUSSIANMAN_GAME_API AInventoryItem : public AActor, public IAnimatable
{
	GENERATED_BODY()

	FName CurrentAnimation;
	FName PreviousAnimation;

protected:
	
	UPROPERTY(Instanced)
	class USkeletalMeshComponent* ItemMesh;

	//TODO
	FItemStack* ItemStack;

	UPROPERTY()
	class UItemsRegistry* Items;

	UPROPERTY()
	class UStateMachine* StateMachine;
	
public:	
	// Sets default values for this actor's properties
	AInventoryItem();

	void SetItemStack(FItemStack& Stack);

	FItemStack& GetItemStack() const;
	
	//Get current item state
	UItemStateBase* GetCurrentState() const;

	//Play animation on item and its owner
	void	PlayAnimation(const FName& AnimationName) override;

	//Get animation duration
	float	GetAnimationDuration(const FName& AnimationName) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
