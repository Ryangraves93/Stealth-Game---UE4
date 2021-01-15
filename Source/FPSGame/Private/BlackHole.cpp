// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	DestroySphere = CreateDefaultSubobject<USphereComponent>(TEXT("Destroy Sphere"));
	RootComponent = DestroySphere;

	GravitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("Gravity Sphere"));
	GravitySphere->SetupAttachment(DestroySphere);


}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GravitySphere)
	{
		TArray<UPrimitiveComponent*> OverlappingComps;
		GravitySphere->GetOverlappingComponents(OverlappingComps);

		TArray<UPrimitiveComponent*> ActorsToBeDestoryed;
		DestroySphere->GetOverlappingComponents(ActorsToBeDestoryed);

		for (UPrimitiveComponent* Comp : OverlappingComps)
		{
			if (Comp && Comp->IsAnySimulatingPhysics())
			{
				FVector TargetLocation = UKismetMathLibrary::GetDirectionUnitVector(Comp->GetComponentLocation(),GetActorLocation());
				float ForceStrength = -2000.f;
				float Radius = GravitySphere->GetScaledSphereRadius();

				//Comp->AddForce(FVector::LeftVector * 200);
				Comp->AddRadialForce(GetActorLocation(), Radius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
			}
		}
		for (UPrimitiveComponent* ActorToDestroy : ActorsToBeDestoryed)
		{
			if (ActorToDestroy && ActorToDestroy->IsAnySimulatingPhysics())
			{
				ActorToDestroy->GetOwner()->Destroy(true);
			}
		}
	}
}



