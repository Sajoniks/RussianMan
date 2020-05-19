// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"
#include "Interface/Interact.h"
#include "TimerManager.h"
#include "RussianMan_Game/RussianMan_Game.h"

TArray<FHitResult> UInteractionComponent::MakeSphereTrace() const
{
	UWorld* World = GetWorld();

	if (World)
	{
		TArray<FHitResult> Hits;
		const FVector Location = TraceSource->GetComponentLocation();
		const FCollisionObjectQueryParams Params{ ECC_INTERACT };
		const auto Shape = FCollisionShape::MakeSphere(SearchRadius);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(GetOwner());
		
		World->SweepMultiByObjectType(Hits, Location, Location, FQuat::Identity, Params, Shape, QueryParams);
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
		Params.AddIgnoredActor(GetOwner());
		Params.AddIgnoredActor(HitResult.GetActor());
		
		return World->LineTraceTestByChannel(Location, HitResult.Location, ECC_Visibility, Params);
	}

	return false;
}

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

};

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

	UObject* Interactable = nullptr;
	
	for (const auto& Hit : ObjectHits)
	{
		if (!MakeObstacleTrace(Hit))
		{
			const FVector Direction = Hit.Location - Center;
			const float Distance = FVector::Dist(Center, Hit.Location);
			const float Dot = FVector::DotProduct(ForwardVector, Direction.GetSafeNormal());

			if (Distance <= MinDistance && MaxThreshold <= Dot)
			{
				MinDistance = Distance;
				MaxThreshold = Dot;
				Interactable = Hit.GetActor();
			}
		}
	}

	CurrentInteractable = Interactable;
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	if (SearchRate > 0.25 && SearchRadius > 50.f && World && !World->GetTimerManager().IsTimerActive(SearchTimerHandle))
	{
		World->GetTimerManager().SetTimer(SearchTimerHandle, this, &UInteractionComponent::PerformScan, SearchRate, true);
		UE_LOG(LogInteract, Log, TEXT("Starting search timer in %s with delay %f s"), *GetName(), SearchRate);
	}
	else
		UE_LOG(LogInteract, Error, TEXT("Failed to start search timer in %s, parameters are:\nDelay: %f;\nRadius: %f"), *GetName(), SearchRate, SearchRadius);
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

