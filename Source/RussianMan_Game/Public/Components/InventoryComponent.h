// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemStack.h"

#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUSSIANMAN_GAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	float Weight;
	uint32 Num;

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	virtual void AddStack(FItemStack& Stack);
	
	virtual bool RemoveStack(int32 Count = 1, const FGameplayTag& ID);
	virtual bool RemoveStack(int32 Count = 1, const FItemStack& Stack);
	virtual bool RemoveStack(int32 Count = 1, int32 Idx);

	virtual bool RemoveStack(const FGameplayTag& ID);
	virtual bool RemoveStack(const FItemStack& Stack);
	virtual bool RemoveStack(int32 Idx);
	
	virtual bool RemoveAll(const FGameplayTag& ID);
	virtual bool RemoveAll(const FItemStack& Stack);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Array of items
	TArray<FItemStack> Inventory;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	const TArray<FItemStack>& GetInventoryArray() const;

};

inline const TArray<FItemStack>& UInventoryComponent::GetInventoryArray() const
{
	return Inventory;
}
