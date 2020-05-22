// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "RussianMan_Game/RussianMan_Game.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::AddStack(UPARAM(ref)FItemStack& Stack)
{
	return AddStack_Impl(Stack);
}

bool UInventoryComponent::AddStack_Impl(FItemStack& Stack)
{
	FillFree(Stack);
	FillPartial(Stack);

	return Stack.Num <= 0;
}

bool UInventoryComponent::RemoveStack(int32 Count, const FGameplayTag& ID)
{
	if (Num > 0)
	{
		const auto Stack = Inventory.FindByPredicate([&ID](const FItemStack& Stack)
		{
			return Stack == ID;
		});

		if (Stack)
		{
			const int32 RemoveCount = FMath::Clamp(Count, 0, Stack->Num);

			if (RemoveCount == Stack->Num)
			{
				--Num;
				Weight -= Stack->Weight();
				*Stack = FItemStack::EmptyStack;
			}
			else
				Stack->Num -= RemoveCount;

			return true;
		}
	}
	return false;
}

bool UInventoryComponent::RemoveStack(int32 Count, const FItemStack& Stack)
{
	return RemoveStack(Count, Stack.ID);
}

bool UInventoryComponent::RemoveStack(int32 Count, int32 Idx)
{
	if (Num > 0)
	{
		if (Inventory.IsValidIndex(Idx))
		{
			FItemStack& Stack = Inventory[Idx];

			const int32 RemoveCount = FMath::Clamp(Count, 0, Stack.Num);

			if (RemoveCount == Stack.Num)
			{
				--Num;
				Weight -= Stack.Weight();
				Stack = FItemStack::EmptyStack;
			}
			else
				Stack.Num -= RemoveCount;

			return true;
		}
	}
	return false;
}

bool UInventoryComponent::RemoveStack(const FGameplayTag& ID)
{
	if (Num > 0)
	{
		const auto Stack = Inventory.FindByPredicate([&ID](const FItemStack& Stack)
		{
			return Stack == ID;
		});

		if (Stack)
		{
			--Num;
			Weight -= Stack->Weight();
			*Stack = FItemStack::EmptyStack;
			return true;
		}
	}
	return false;
}

bool UInventoryComponent::RemoveStack(const FItemStack& Stack)
{
	return RemoveStack(Stack.ID);
}

bool UInventoryComponent::RemoveStack(int32 Idx)
{
	if (Num > 0)
	{
		if (Inventory.IsValidIndex(Idx))
		{
			--Num;
			Weight -= Inventory[Idx].Weight();
			Inventory[Idx] = FItemStack::EmptyStack;
			return true;
		}
	}
	return false;
}

bool UInventoryComponent::RemoveAll(const FGameplayTag& ID)
{
	if (Num > 0)
	{
		bool bRemoved = false;
		
		auto Stack = Inventory.FindByPredicate([&ID](const FItemStack& Stack)
		{
			return Stack == ID;
		});

		while (Stack && Num > 0)
		{
			bRemoved = true;
			--Num;
			Weight -= Stack->Weight();
			*Stack = FItemStack::EmptyStack;

			Stack = Inventory.FindByPredicate([&ID](const FItemStack& Stack)
			{
				return Stack == ID;
			});
		}

		return bRemoved;
	}

	return false;
}

bool UInventoryComponent::RemoveAll(const FItemStack& Stack)
{
	return RemoveAll(Stack.ID);
}

uint32 UInventoryComponent::NextIndex(const FItemStack& ItemStack, uint32 Index) const
{
	if (Inventory.IsValidIndex(Index) && ItemStack.IsValid())
	{
		for (auto It = Inventory.CreateConstIterator() + Index; It; ++It)
		{
			if (ItemStack.ID.MatchesTagExact(It->ID))
			{
				const int32 Delta = FMath::Abs(It->Max() - It->Num);

				if (Delta > 0)
					return It.GetIndex();
			}
		}
	}
	
	return -1;
}

uint32 UInventoryComponent::NextFreeIndex(uint32 Index) const
{
	if (Inventory.IsValidIndex(Index))
	{
		for (auto It = Inventory.CreateConstIterator() + Index; It; ++It)
			if (*It == FItemStack::EmptyStack)
			{
				return It.GetIndex();
			}
	}

	return -1;
}

void UInventoryComponent::FillFree(FItemStack& Stack)
{
	if (Stack.IsValid())
	{
		uint32 Idx = NextFreeIndex(0);

		const int32 MaxNum = Stack.Max();
		const float ItemWeight = Stack.Weight() / Stack.Num;

		while (Inventory.IsValidIndex(Idx))
		{
			const int32 Delta = FMath::Clamp(Stack.Num, 0, MaxNum);

			Inventory[Idx] = Stack;
			Inventory[Idx].Num = Delta;
			Stack.Num -= Delta;

			Num++;
			Weight += Delta * ItemWeight;

			if (Stack.Num <= 0)
			{
				Stack = FItemStack::EmptyStack;
				return;
			}

			Idx = NextFreeIndex(Idx + 1);
		}
	}
}

void UInventoryComponent::FillPartial(FItemStack& Stack)
{
	if (Stack.IsValid())
	{
		uint32 Idx = NextIndex(Stack, 0);

		const int32 MaxNum = Stack.Max();
		const float ItemWeight = Stack.Weight() / Stack.Num;

		while (Inventory.IsValidIndex(Idx))
		{
			int32 Delta = FMath::Abs(MaxNum - Inventory[Idx].Num);
			Delta = FMath::Clamp(Delta, 0, Stack.Num);

			Inventory[Idx].Num += Delta;
			Stack.Num -= Delta;

			Weight += Delta * ItemWeight;

			if (Stack.Num <= 0)
			{
				Stack = FItemStack::EmptyStack;
				return;
			}

			Idx = NextIndex(Stack, Idx + 1);
		}
	}
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

