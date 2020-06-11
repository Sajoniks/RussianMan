// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"
#include "Character/RussianCharacter.h"
#include "Actor/Inventory/InventoryItem.h"

bool UWeaponComponent::HandleSet(AInventoryItem*& ItemToSet, FItemStack& StackToSet) const
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

		ItemToSet->SetItemStack(StackToSet);
		return true;
	}

	return false;
}

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
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

bool UWeaponComponent::SetMainWeapon(FItemStack& WeaponStack)
{
	return HandleSet(MainWeapon, WeaponStack);
}

bool UWeaponComponent::SetSecondaryWeapon(FItemStack& WeaponStack)
{
	return HandleSet(SecondaryWeapon, WeaponStack);
}

bool UWeaponComponent::SetMeleeWeapon(FItemStack& WeaponStack)
{
	return HandleSet(MeleeWeapon, WeaponStack);
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