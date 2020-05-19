// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Interactable/InteractableBase.h"
#include "Components/MeshComponent.h"
#include "RussianMan_Game/RussianMan_Game.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AInteractableBase::DrawToCustomDepth(bool bDraw)
{
	for (const auto& Comp : ObjectTree)
	{
		Comp->SetRenderCustomDepth(bDraw);
	}
}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

	ObjectTree.Empty();
	
	const auto Root = GetRootComponent();
	if (Root)
	{
		TArray<USceneComponent*> Comps;
		Root->GetChildrenComponents(true, Comps);
		Comps.Add(Root);

		for (const auto& Comp : Comps)
		{
			auto Mesh = Cast<UMeshComponent>(Comp);
			if (Mesh)
			{
				ObjectTree.Add(Mesh);
				Mesh->SetCollisionObjectType(ECC_INTERACT);
				Mesh->SetCollisionProfileName("Pickup");
			}
		}
	}
	
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

