// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Interactable/Pickup.h"
#include "Data/ItemsRegistry.h"

#if WITH_EDITOR
#include "UObject/ConstructorHelpers.h"
#endif

APickup::APickup()
{
#if WITH_EDITOR
	//const auto RegistryObject = ConstructorHelpers::FObjectFinder<UItemsRegistry>(TEXT(""));
	//ItemsRegistry = RegistryObject.Object;
#endif
}

void APickup::MakePickupFromStack(FItemStack& Stack)
{
	
}

#if WITH_EDITOR
void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (ItemsRegistry)
	{
		WorldMesh->SetStaticMesh(ItemsRegistry->GetWorldMesh(Item.ID));
	}
}
#endif

void APickup::BeginPlay()
{
	if (!ItemsRegistry)
	{
		//TODO 
	}
}

bool APickup::Interact_Implementation(ARussianCharacter* Caller)
{
	return true;
}
