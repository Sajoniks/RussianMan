// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RussianCharacter.h"
#include "Components/InteractionComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ARussianCharacter::ARussianCharacter(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	InteractionComponent = ObjectInitializer.CreateDefaultSubobject<UInteractionComponent>(this, TEXT("Interaction Component"));

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("First Person Camera");
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

}

