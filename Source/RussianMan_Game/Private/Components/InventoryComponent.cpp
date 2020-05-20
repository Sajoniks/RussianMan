// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "RussianMan_Game/RussianMan_Game.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInventoryComponent::AddStack(FItemStack& Stack)
{
	UE_LOG(LogInventory, Warning, TEXT("Can't add items to container, %s, ignoring"), *GetOwner()->GetName());
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
				Stack = FItemStack::EmptyStack;
				--Num;
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
			*Stack = FItemStack::EmptyStack;
			--Num;
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
			Inventory[Idx] = FItemStack::EmptyStack;
			--Num;
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

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

