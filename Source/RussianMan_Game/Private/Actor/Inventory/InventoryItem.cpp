// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Inventory/InventoryItem.h"
#include "State/StateMachine/StateMachine.h"
#include "Data/ItemsRegistry.h"
#include "RussianGameInstance.h"
#include "Data/ItemStack.h"

FItemStack& AInventoryItem::GetItemStack() const
{
	return *ItemStack;
}

// Sets default values
AInventoryItem::AInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Item Mesh");
	ItemStack = new FItemStack();
	*ItemStack = FItemStack::EmptyStack;
}

// Called when the game starts or when spawned
void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInventoryItem::SetItemStack(FItemStack& Stack)
{
	if (Stack.IsValid())
	{
		ItemStack = &Stack;

		if (!Items)
		{
			Items = URussianGameInstance::GetItemRegistry();
		}
		
		if (Items)
		{
			const FGameplayTag& ID = ItemStack->ID;
			
			ItemMesh->SetSkeletalMesh(Items->GetViewportMesh(ID));
			StateMachine = Items->GetStateMachine(ID);
			
			//
			//Other things to init
		}
	}
}

UItemStateBase* AInventoryItem::GetCurrentState() const
{
	if (StateMachine)
		return StateMachine->GetCurrentState();

	return nullptr;
}

void AInventoryItem::PlayAnimation(const FName& AnimationName)
{
	if (AnimationName.IsValid() && !AnimationName.IsNone())
	{
	
		
	}
}

float AInventoryItem::GetAnimationDuration(const FName& AnimationName) const
{
	if (AnimationName.IsValid() && !AnimationName.IsNone())
	{
		return 1;
	}
	
	return 0.f;
}

// Called every frame
void AInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

