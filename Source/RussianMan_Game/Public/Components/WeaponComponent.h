// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class UInventoryComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUSSIANMAN_GAME_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	UInventoryComponent* BoundInventory;

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	void BindWithInventory(UInventoryComponent* InventoryComponent);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
