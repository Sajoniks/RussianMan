// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"
#include "TimerManager.h"

TArray<FHitResult> UInteractionComponent::MakeSphereTrace() const
{
	UWorld* World = GetWorld();

	if (World)
	{
		TArray<FHitResult> Hits;
		FVector Location = TraceSource->GetComponentLocation();
		FCollisionObjectQueryParams Params{ ECC_GameTraceChannel1 };
		
		World->LineTraceMultiByObjectType(Hits, Location, Location, Params);

		return Hits; 
	}

	return TArray<FHitResult>();
}

bool UInteractionComponent::MakeObstacleTrace(const FHitResult& HitResult) const
{
	UWorld* World = GetWorld();
	if (World)
	{
		FVector Location = TraceSource->GetComponentLocation();
		FCollisionQueryParams Params;
		Params.AddIgnoredActors({ GetOwner(), HitResult.Actor });
		
		return World->LineTraceTestByChannel(Location, HitResult.Location, ECC_Visibility, Params);
	}

	return false;
}

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	UWorld* World = GetWorld();
	
	if (SearchRate > 0.25 && World && !World->GetTimerManager().IsTimerActive(SearchTimerHandle))
		World->GetTimerManager().SetTimer(SearchTimerHandle, this, &UInteractionComponent::PerformScan, SearchRate, true);
}

void UInteractionComponent::SetTraceSource(USceneComponent* Source)
{
	TraceSource = Source;
}

void UInteractionComponent::PerformScan()
{	
	const FVector Center = GetOwner()->GetActorLocation();
	const FVector ForwardVector = TraceSource->GetComponentRotation().Vector();
	
	const auto ObjectHits = MakeSphereTrace();
	
	float MinDistance = SearchRadius;
	float MaxThreshold = -1.f;

	IInteract* Interactable = nullptr;
	
	for (const auto& Hit : ObjectHits)
	{
		if (!MakeObstacleTrace(Hit))
		{
			const FVector Direction = Hit.Location - Center;
			const float Distance = FVector::Dist(Center, Hit.Location);
			const float Dot = FVector::DotProduct(ForwardVector, Direction.GetSafeNormal());

			if (Distance < MinDistance && MaxThreshold < Dot)
			{
				MinDistance = Distance;
				MaxThreshold = Dot;
				Interactable = Cast<IInteract>(Hit.Actor);
			}
		}
	}

	CurrentInteractable = Interactable;
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

