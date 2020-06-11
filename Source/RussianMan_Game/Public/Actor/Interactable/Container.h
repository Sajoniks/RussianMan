// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Interactable/InteractableBase.h"
#include "Container.generated.h"

UCLASS()
class RUSSIANMAN_GAME_API AContainer : public AInteractableBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, Category="Visual", Instanced)
	class USkeletalMeshComponent* WorldMesh;
	
public:	
	// Sets default values for this actor's properties
	AContainer();

	UFUNCTION(BlueprintCallable, Category="Get")
	class UInventoryComponent* GetInventory() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
