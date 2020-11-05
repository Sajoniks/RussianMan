// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"
#include "Character/RussianCharacter.h"
#include "Actor/Inventory/InventoryItem.h"

#include "RussianMan_Game/RussianMan_Game.h"

void UWeaponComponent::HandleSet(AInventoryItem*& ItemToSet, FItemStack& StackToSet) const
{
	if (StackToSet.IsValid())
	{
		if (!ItemToSet)
		{
			auto Owner = GetTypedOuter<ARussianCharacter>();
			if (Owner)
				ItemToSet = Owner->GetWorld()->SpawnActor<AInventoryItem>();
			
			ItemToSet->AttachToComponent(FP_BoundMesh, { EAttachmentRule::SnapToTarget, true }, "Weapon_Bone_R");
		}

		UE_LOG(LogInventory, All, TEXT("Setting %s to %s"), *ItemToSet->GetName(), *StackToSet.ID.ToString());
		ItemToSet->SetItemStack(StackToSet);
		UE_LOG(LogInventory, All, TEXT("Now %s contains %s"), *ItemToSet->GetName(), *ItemToSet->GetItemStack().ID.ToString());
	}
}

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	Hotbar.SetNum(5);
}

void UWeaponComponent::BindWithInventory(UInventoryComponent* InventoryComponent)
{
	if (InventoryComponent != BoundInventory)
	{
		BoundInventory = InventoryComponent;

		//We want to hold both meshes of owning actor 
		auto Owner = GetTypedOuter<ARussianCharacter>();
		if (Owner)
		{
			FP_BoundMesh = Owner->GetFirstPersonMesh();
			TP_BoundMesh = Owner->GetMesh();
		}
	}
	//TODO 
}

void UWeaponComponent::SetMainWeapon(FItemStack& WeaponStack)
{
	MainWeaponStack = WeaponStack;
	HandleSet(MainWeapon, MainWeaponStack);
}

void UWeaponComponent::SetSecondaryWeapon(FItemStack& WeaponStack)
{
	SecondaryWeaponStack = WeaponStack;
	HandleSet(SecondaryWeapon, SecondaryWeaponStack);
}

void UWeaponComponent::SetMeleeWeapon(FItemStack& WeaponStack)
{
	MeleeWeaponStack = WeaponStack;
	HandleSet(MeleeWeapon, MeleeWeaponStack);
}

AInventoryItem* UWeaponComponent::GetCurrentItem() const
{
	return SelectedItem;
}

const UWeaponComponent::FHotbarArray& UWeaponComponent::GetHotbar() const
{
	return Hotbar;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}