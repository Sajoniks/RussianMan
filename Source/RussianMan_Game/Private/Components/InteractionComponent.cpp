// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"
#include "Interface/Interact.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "RussianMan_Game/RussianMan_Game.h"

std::pair<FVector, FVector> BoundingBoxData(AActor* Actor)
{
	if (Actor)
	{
		FVector V1, V2;
		Actor->GetActorBounds(true, V1, V2);
		return std::make_pair(V1, V2);
	}

	return std::pair<FVector, FVector>();
}

TArray<FHitResult> UInteractionComponent::MakeSphereTrace() const
{
	UWorld* World = GetWorld();

	if (World)
	{
		TArray<FHitResult> Hits;
		
		//TODO 
		const FVector Location = TraceSource ? TraceSource->GetComponentLocation() : GetOwner()->GetActorLocation() + 50;
		const FCollisionObjectQueryParams Params{ ECC_INTERACT };
		const auto Shape = FCollisionShape::MakeSphere(SearchRadius);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(GetOwner());

		if (bShowDebugInfo)
		{
			DrawDebugSphere(World, Location, SearchRadius, 32, FColor::Blue, false, SearchRate, 0, 0.1);
		}
		
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
		//TODO 
		const FVector Location = TraceSource ? TraceSource->GetComponentLocation() : GetOwner()->GetActorLocation() + 50;
		const FVector EndLocation = BoundingBoxData(HitResult.GetActor()).first;
		
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetOwner());
		Params.AddIgnoredActor(HitResult.GetActor());

		if (bShowDebugInfo)
		{
			DrawDebugLine(World, Location, EndLocation, FColor::Orange, false, SearchRate, 0, 0.1);
			DrawDebugPoint(World, EndLocation, 0.2, FColor::Red, false, SearchRate);
		}
		
		return World->LineTraceTestByChannel(Location, EndLocation, ECC_Visibility, Params);
	}

	return false;
}

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::SetTraceSource(USceneComponent* Source)
{
	TraceSource = Source;
}

void UInteractionComponent::PerformScan()
{	
	const FVector Center = GetOwner()->GetActorLocation();
	const FVector ForwardVector = TraceSource ? TraceSource->GetComponentRotation().Vector() : GetOwner()->GetActorRotation().Vector();
	
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

			if (Distance <= MinDistance && MaxThreshold <= Dot && Dot >= Threshold)
			{
				MinDistance = Distance;
				MaxThreshold = Dot;
				Interactable = Hit.GetActor();
			}
		}
	}

	CurrentInteractable = Interactable;

	//TODO  
	if (bShowDebugInfo && GEngine)
	{
		AActor* Target = Cast<AActor>(CurrentInteractable.GetObject());

		const FString Name = Target ? Target->GetName() : "None";
		const float Distance = Target ? FVector::Dist(GetOwner()->GetActorLocation(), Target->GetActorLocation()) : 0;

		const FVector LookDirection = TraceSource ? TraceSource->GetComponentRotation().Vector() : GetOwner()->GetActorRotation().Vector();
		const FVector Direction = Target ? (Target->GetActorLocation() - GetOwner()->GetActorLocation()) : FVector{};

		const float Dot = FVector::DotProduct(LookDirection, Direction);

		const auto MessageName = FString::Printf(TEXT("Current interaction target: %s"), *Name);
		const auto MessageDistance = FString::Printf(TEXT("Distance: %f"), Distance);
		const auto MessageDot = FString::Printf(TEXT("Dot: %f"), Dot);

		GEngine->AddOnScreenDebugMessage(0, SearchRate, FColor::Green, MessageName);
		GEngine->AddOnScreenDebugMessage(1, SearchRate, FColor::Green, MessageDistance);
		GEngine->AddOnScreenDebugMessage(2, SearchRate, FColor::Green, MessageDot);
	}
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
}

