// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Interactable/Pickup.h"

#include "RussianGameInstance.h"
#include "Data/ItemsRegistry.h"
#include "Data/Wrappers/WrapperBase.h"
#include "RussianMan_Game/RussianMan_Game.h"

#if WITH_EDITOR
#include "UObject/ConstructorHelpers.h"
#endif

void APickup::Update()
{
	if (ItemsRegistry)
	{
		WorldMesh->SetStaticMesh(ItemsRegistry->GetWorldMesh(Item.ID));
		Wrapper = ItemsRegistry->GetWrapper(Item.ID);

		if (Wrapper)
			Wrapper->SetStack(Item);
	}
}

APickup::APickup()
{
	ItemCount = 1;
	
#if WITH_EDITOR
	const auto RegistryObject = ConstructorHelpers::FObjectFinder<UItemsRegistry>(TEXT("ItemsRegistry'/Game/Blueprint/Data/BP_ItemsRegistry.BP_ItemsRegistry'"));
	ItemsRegistry = RegistryObject.Object;
#endif

	WorldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("World Mesh"));
	WorldMesh->SetSimulatePhysics(true);
	SetRootComponent(WorldMesh);
}

void APickup::MakePickupFromStack(FItemStack& Stack)
{
	Move(Item, Stack);
	Stack = FItemStack::EmptyStack;

	Update();
}

#if WITH_EDITOR
void APickup::OnConstruction(const FTransform& Transform)
{
	if (ItemsRegistry)
	{
		WorldMesh->SetStaticMesh(ItemsRegistry->GetWorldMesh(ID));
		UE_LOG(LogItemsRegistry, Log, TEXT("Updating %s because one of fields has changed"), *GetName());
	}
}
#endif

void APickup::BeginPlay()
{
	Super::BeginPlay();

	if (!ItemsRegistry)
	{
		ItemsRegistry = URussianGameInstance::GetItemRegistry();
	}

	if (ItemsRegistry)
	{
		if (!WorldMesh->GetStaticMesh())
			WorldMesh->SetStaticMesh(ItemsRegistry->GetWorldMesh(ID));

		Item = ItemsRegistry->MakeStackFromID(ID);
		Item.Num = ItemCount;

		Update();
	}
}

bool APickup::Interact_Implementation(ARussianCharacter* Caller)
{
	if (Wrapper)
	{
		const bool bResult = Wrapper->Unwrap(Caller);

		if (bResult)
		{
			Wrapper = nullptr;
			Destroy();
		}
		else
		{
			//TODO 
		}

		return bResult;
	}

	return false;
}
