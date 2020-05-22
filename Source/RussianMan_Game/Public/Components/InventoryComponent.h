// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemStack.h"

#include "InventoryComponent.generated.h"

enum class EFillType : uint8
{
	Free,
	Partial
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUSSIANMAN_GAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	/**Spreads given stack across inventory and fills with it free slots
	 * @param Stack Stack to add
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory|Action")
	bool AddStack(UPARAM(ref)FItemStack& Stack);

	/**Removes given count of given item ID
	 * @param Count Count to remove
	 * @param ID Item ID
	 * @return true, if item was removed
	 */
	bool RemoveStack(int32 Count, const FGameplayTag& ID);
	
	/**Removes given count of given item stack
	 * @param Count Count to remove
	 * @param Stack Item stack
	 * @return true, if item was removed
	 */
	bool RemoveStack(int32 Count, const FItemStack& Stack);

	/**Removes given count at given inventory index
	 * @param Count Count to remove
	 * @param Idx Inventory index
	 * @return true, if item was removed
	 */
	bool RemoveStack(int32 Count, int32 Idx);

	/**Removes one item slot with given ID
	 * @param ID Item ID
	 * @return true, if item was removed
	 */
	bool RemoveStack(const FGameplayTag& ID);

	/**Removes one item slot with given stack
	 * @param Stack Item stack
	 * @return true, if item was removed
	 */
	bool RemoveStack(const FItemStack& Stack);

	/**Removes one item slot with given index
	 * @param Idx Inventory index
	 * @return true, if item was removed
	 */
	bool RemoveStack(int32 Idx);

	/**Completely wipes items from inventory with given ID
	 * @param ID Item ID
	 * @return true, if there was at least one removal 
	 */
	bool RemoveAll(const FGameplayTag& ID);

	/**Completely wipes items from inventory with given stack
	 * @param Stack Item stack
	 * @return true, if there was at least one removal
	 */
	bool RemoveAll(const FItemStack& Stack);
	
protected:

	//Current weight of this container
	float Weight;

	//Current occupied slots
	uint32 Num;

	virtual bool AddStack_Impl(FItemStack& Stack);

	/**Finds next index where item stack is not full
	 * @param Stack to compare
	 * @param Index Index to start from
	 * @return Index of this slot, or -1, if no slot found
	 */
	uint32 NextIndex(const FItemStack& Stack, uint32 Index = 0) const;

	/**Finds next index where item stack is empty
	 * @param Index Index to start from
	 * @return Index of this slot, or -1, if no slot found
	 */
	uint32 NextFreeIndex(uint32 Index = 0) const;

	void FillFree(FItemStack& Stack);

	void FillPartial(FItemStack& Stack);
	
	// Called when the game starts
	virtual void BeginPlay() override;

	//Items array
	UPROPERTY(EditInstanceOnly, Category="Container")
	TArray<FItemStack> Inventory;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Get read - only array of items
	const TArray<FItemStack>& GetInventoryArray() const;

};

inline const TArray<FItemStack>& UInventoryComponent::GetInventoryArray() const
{
	return Inventory;
}
