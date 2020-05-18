// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interact.h"
#include "InteractableBase.generated.h"

UCLASS(Blueprintable, Abstract)
class RUSSIANMAN_GAME_API AInteractableBase : public AActor, public IInteract
{
	GENERATED_BODY()

	UPROPERTY()
	//Holds all meshes of object (for drawing to custom depth)
	TArray<class UMeshComponent*> ObjectTree;
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

	/*Interact Interface*/
	
	void DrawToCustomDepth(bool bDraw) override;
	bool Interact_Implementation(ARussianCharacter* Caller) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

inline bool AInteractableBase::Interact_Implementation(ARussianCharacter* Caller)
{
	return false;
}
