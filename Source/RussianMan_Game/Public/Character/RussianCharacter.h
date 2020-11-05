// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/Animatable.h"
#include "Interface/Inventory.h"
#include "RussianCharacter.generated.h"

class UInteractionComponent;
class UPlayerInventoryComponent;
class UInventoryComponent;
class UWeaponComponent;
class UCameraComponent;

struct FAnimationSet;
struct FItemStack;

UCLASS(Blueprintable, CustomConstructor)
class RUSSIANMAN_GAME_API ARussianCharacter : public ACharacter, public IAnimatable, public IInventory
{
	GENERATED_BODY()

	FAnimationSet* AnimationSet;

	UPROPERTY(VisibleDefaultsOnly, Category="Interaction|Components", Instanced)
	UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Inventory|Components", Instanced)
	UPlayerInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon|Components", Instanced)
	UWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Camera", Instanced)
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleDefaultsOnly, Category="Mesh", Instanced)
	USkeletalMeshComponent* FirstPersonMesh;

	void Interact();

	//Draw interaction schema
	UFUNCTION(Exec)
	void ShowInteractDebugInformation(bool bDebug);

	//Cheat 
	UFUNCTION(Exec)
	void MakeInventoryInfinite(bool bInfinity);

public:
	// Sets default values for this character's properties
	ARussianCharacter(const FObjectInitializer& ObjectInitializer);

	void MoveForward(float Value);
	void MoveRight(float Value);

	//Get player inventory as a component
	UFUNCTION(BlueprintCallable, Category="Inventory|Get")
	UInventoryComponent* GetInventory() const override;

	//Inventory type
	EInventoryType GetInventoryType() const override { return EInventoryType::PlayerInventory; }

	//Get player weapons as a component
	UFUNCTION(BlueprintCallable, Category="Inventory|Get")
	UWeaponComponent* GetWeapons() const;

	UFUNCTION(BlueprintCallable, Category="Get")
	USkeletalMeshComponent* GetFirstPersonMesh() const;
	
	bool IsPlayerControlled() const override;

	//Play animation according current item
	void PlayAnimation(const FName& AnimationName) override;

	//Get animation duration according current item
	float GetAnimationDuration(const FName& AnimationName) const override;

	const FItemStack& GetCurrentHeldItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
