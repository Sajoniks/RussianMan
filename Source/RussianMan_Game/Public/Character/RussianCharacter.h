// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RussianCharacter.generated.h"

class UInteractionComponent;
class UPlayerInventoryComponent;
class UWeaponComponent;
class UCameraComponent;

UCLASS(Blueprintable, CustomConstructor)
class RUSSIANMAN_GAME_API ARussianCharacter : public ACharacter
{
	GENERATED_BODY()

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
	
	UFUNCTION(Exec)
	void ShowInteractDebugInformation(bool bDebug);

	UFUNCTION(Exec)
	void MakeInventoryInfinite(bool bInfinity);

public:
	// Sets default values for this character's properties
	ARussianCharacter(const FObjectInitializer& ObjectInitializer);

	void MoveForward(float Value);
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category="Inventory|Get")
	UPlayerInventoryComponent* GetInventory() const;

	UFUNCTION(BlueprintCallable, Category="Inventory|Get")
	UWeaponComponent* GetWeapons() const;

	UFUNCTION(BlueprintCallable, Category="Get")
	USkeletalMeshComponent* GetFirstPersonMesh() const;
	
	bool IsPlayerControlled() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
