// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RussianCharacter.h"
#include "Components/InteractionComponent.h"
#include "Camera/CameraComponent.h"

void ARussianCharacter::Interact()
{
	if (InteractionComponent)
	{
		
	}
}

void ARussianCharacter::ShowInteractDebugInformation(bool bDebug)
{
	if (InteractionComponent)
		InteractionComponent->bShowDebugInfo = bDebug;
}

// Sets default values
ARussianCharacter::ARussianCharacter(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	InteractionComponent = ObjectInitializer.CreateDefaultSubobject<UInteractionComponent>(this, TEXT("Interaction Component"));

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("First Person Camera");
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->SetupAttachment(GetRootComponent());
}

void ARussianCharacter::MoveForward(float Value)
{
	const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ARussianCharacter::MoveRight(float Value)
{
	const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
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

