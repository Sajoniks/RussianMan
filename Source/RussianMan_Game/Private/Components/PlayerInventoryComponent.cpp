// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerInventoryComponent.h"
#include "RussianMan_Game/RussianMan_Game.h"

#define POCKET_SIZE (uint8)2
#define POCKET_WEIGHT 1.f

bool UPlayerInventoryComponent::AddStack_Impl(FItemStack& Stack)
{
	if (bIgnoreParams)
	{
		return Super::AddStack_Impl(Stack);
	}

	const auto Count = StripStack(Stack);

	if (Count > 0)
	{
		FItemStack StackCopy = Stack;
		StackCopy.Num = Count;

		UE_LOG(LogInventory, Log, TEXT("Adding %d items to %s inventory"), Count, *GetOwner()->GetName());
		const bool bFullAdded = Super::AddStack_Impl(StackCopy);

		const int32 AddedCount = Count - StackCopy.Num;
		Stack.Num -= AddedCount;

		//In count we have items left
		UE_LOG(LogInventory, Log, TEXT("Added %d items, %d items left in stack"), AddedCount, Stack.Num);

		if (Stack.Num == 0)
			Stack = FItemStack::EmptyStack;

		return bFullAdded && Stack.Num == 0;
	}

	UE_LOG(LogInventory, Warning, TEXT("%s inventory is full, nothing to add.\nStats:\nWeight: %f/%f;\nFree slots: %d/%d;"),
			*GetOwner()->GetName(),
			Weight, MaxWeight,
			Num, MaxNum
	);
	
	return false;
}

uint32 UPlayerInventoryComponent::StripStack(const FItemStack& Stack) const
{
	if (Stack.IsValid())
	{
		const float ItemWeight = Stack.Weight() / Stack.Num;
		const float EmptySpace = MaxWeight - Weight;
		const int32 EmptySlots = Stack.Max()*(MaxNum - Num);
		
		int32 Count = FMath::FloorToInt(EmptySpace/ItemWeight);
		Count = FMath::Clamp(Count, 0, EmptySlots);
		Count = FMath::Clamp(Stack.Num, 0, Count);
		
		return Count;
	}

	return 0;
}

UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	Inventory.AddDefaulted(POCKET_SIZE);
	MaxWeight = POCKET_WEIGHT;
}

bool UPlayerInventoryComponent::SetContainer(FItemStack& NewContainer)
{
	if (!bIgnoreParams)
	{
		if (NewContainer.IsValid())
		{
			const uint32 NewNum = NewContainer.GetParameter<float>("Param.Container.MaxNum");
			const float NewWeight = NewContainer.GetParameter<float>("Param.Container.MaxWeight");

			if (ContainerID.IsValid() && NewNum <= Num && NewWeight <= Weight)
			{
				//throw this shit!
				MaxNum = NewNum;
				MaxWeight = NewWeight;

				ContainerID = NewContainer.ID;
			}
		}
	}
	
	return false;
}

void UPlayerInventoryComponent::MakeInfinite(bool bInfinite)
{

}
