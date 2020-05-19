// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Interactable/InteractableBase.h"
#include "Data/ItemStack.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class RUSSIANMAN_GAME_API APickup : public AInteractableBase
{
	GENERATED_BODY()

#if WITH_EDITOR
	class UItemsRegistry* ItemsRegistry;
#endif

	class UStaticMeshComponent* WorldMesh;

	UPROPERTY(EditAnywhere, Category="Inventory")
	struct FItemStack Item;

public:

	APickup();

	/**Prepares this pickup to be properly working
	 *@param Stack Stack that will be wrapped with this pickup
	 *@note If stack is correct, it will be nulled
	 */
	void MakePickupFromStack(FItemStack& Stack);

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void BeginPlay() override;

	/*Interact interface*/

	bool Interact_Implementation(ARussianCharacter* Caller) override;
};
