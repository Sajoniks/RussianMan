// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RussianCharacter.h"
#include "Components/InteractionComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/PlayerInventoryComponent.h"
#include "Camera/CameraComponent.h"

void ARussianCharacter::Interact()
{
	if (InteractionComponent)
	{
		bool bResult = InteractionComponent->Interact();
	}
}

void ARussianCharacter::ShowInteractDebugInformation(bool bDebug)
{
	if (InteractionComponent)
		InteractionComponent->bShowDebugInfo = bDebug;
}

void ARussianCharacter::MakeInventoryInfinite(bool bInfinity)
{
	
}

// Sets default values
ARussianCharacter::ARussianCharacter(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	InteractionComponent = ObjectInitializer.CreateDefaultSubobject<UInteractionComponent>(this, TEXT("Interaction Component"));
	WeaponComponent = ObjectInitializer.CreateDefaultSubobject<UWeaponComponent>(this, TEXT("Weapon Component"));
	InventoryComponent = ObjectInitializer.CreateDefaultSubobject<UPlayerInventoryComponent>(this, TEXT("Inventory Component"));
	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("First Person Camera");
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->SetupAttachment(GetRootComponent());

	WeaponComponent->BindWithInventory(InventoryComponent);
}

void ARussianCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ARussianCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

UPlayerInventoryComponent* ARussianCharacter::GetInventory() const
{
	return InventoryComponent;
}

bool ARussianCharacter::IsPlayerControlled() const
{
	return GetController()->IsPlayerController();
}

// Called when the game starts or when spawned
void ARussianCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARussianCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARussianCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ARussianCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ARussianCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ARussianCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &ARussianCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ARussianCharacter::Interact);
}

