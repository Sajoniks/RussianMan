// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RussianCharacter.generated.h"

class UInteractionComponent;
class UCameraComponent;

UCLASS(Blueprintable, CustomConstructor)
class RUSSIANMAN_GAME_API ARussianCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category="Interaction|Components", Instanced)
	UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Camera", Instanced)
	UCameraComponent* FirstPersonCamera;

	void Interact();

	UFUNCTION(Exec)
	void ShowInteractDebugInformation(bool bDebug);

public:
	// Sets default values for this character's properties
	ARussianCharacter(const FObjectInitializer& ObjectInitializer);

	void MoveForward(float Value);
	void MoveRight(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
