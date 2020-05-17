// Fill out your copyright notice in the Description page of Project Settings.


#include "RussianCharacter.h"

// Sets default values
ARussianCharacter::ARussianCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

