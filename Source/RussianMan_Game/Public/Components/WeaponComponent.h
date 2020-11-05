// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemStack.h"
#include "WeaponComponent.generated.h"

class UInventoryComponent;
class AInventoryItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUSSIANMAN_GAME_API UWeaponComponent : public UActorComponent
{
	using FHotbarArray = TArray<FItemStack*>;
	
	GENERATED_BODY()

	UPROPERTY()
	//Component to communicate with
	UInventoryComponent* BoundInventory;

	UPROPERTY()
	USkeletalMeshComponent* FP_BoundMesh;

	UPROPERTY()
	USkeletalMeshComponent* TP_BoundMesh;

	UPROPERTY()
	AInventoryItem* MainWeapon;

	UPROPERTY()
	AInventoryItem* SecondaryWeapon;

	UPROPERTY()
	AInventoryItem* MeleeWeapon;

	UPROPERTY()
	AInventoryItem* SelectedItem;

	FItemStack MainWeaponStack;
	FItemStack SecondaryWeaponStack;
	FItemStack MeleeWeaponStack;

	FHotbarArray Hotbar;

	/**Little helper function that contains boilerplate code for item setting
	 * @param ItemToSet		Item where stack will be applied
	 * @param StackToSet	Applying stack
	 */
	void HandleSet(AInventoryItem*& ItemToSet, FItemStack& StackToSet) const;

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	/**Bind this component to inventory so it can communicate and work
	 * @param InventoryComponent Inventory to bind
	 */
	void BindWithInventory(UInventoryComponent* InventoryComponent);

	/*TODO*/
	UFUNCTION(BlueprintCallable, Category="WeaponComponent|Action")
	void SetMainWeapon(UPARAM(ref)FItemStack& WeaponStack);

	UFUNCTION(BlueprintCallable, Category = "WeaponComponent|Action")
	void SetSecondaryWeapon(UPARAM(ref)FItemStack& WeaponStack);

	UFUNCTION(BlueprintCallable, Category="WeaponComponent|Action")
	void SetMeleeWeapon(UPARAM(ref)FItemStack& WeaponStack);

	AInventoryItem* GetCurrentItem() const;

	const FHotbarArray& GetHotbar() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
