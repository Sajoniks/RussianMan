// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class IInteract;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUSSIANMAN_GAME_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

	struct FTimerHandle SearchTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	//Delay (in sec) between search traces 
	float SearchRate;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	//Radius of scan sphere
	float SearchRadius;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	//Min distance between aim point and interactable object center
	float Threshold;

	UPROPERTY()
	USceneComponent* TraceSource;

	UPROPERTY()
	IInteract* CurrentInteractable;

	/*Helpers*/

	//Makes multi sphere trace to collect interactable objects in radius
	TArray<FHitResult> MakeSphereTrace() const;

	//Makes single line trace by visibility channel to check obstacles
	bool MakeObstacleTrace(const FHitResult& HitResult) const;
	
public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	void SetTraceSource(USceneComponent* Source);
	void PerformScan();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
