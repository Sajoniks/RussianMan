// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Inventory/MainWeapon.h"
#include "Character/RussianCharacter.h"
#include "Components/WeaponComponent.h"

void UMainWeapon::OnSelection(ARussianCharacter* Caller) const
{
	//TODO
	auto Comp = Caller->GetWeapons();
	/*if (Comp)
		Comp->SelectWeapon(EWeaponType::Main);*/
}
