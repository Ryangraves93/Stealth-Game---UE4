// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetBoxExtent(FVector(200.f));
	CollisionComp->SetHiddenInGame(true);
	RootComponent = CollisionComp;

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::HandleOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(CollisionComp);

	ForwardMomentum = 2000.f;
	UpwardMomentum = 2000.f;
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();

}

void ALaunchPad::HandleOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* Mypawn = Cast<AFPSCharacter>(OtherActor);

	if (Mypawn)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchParticle, GetActorLocation());

		const FVector ActorForwardVec = Mypawn->GetActorForwardVector();
		const FVector AddForce = ActorForwardVec * ForwardMomentum + FVector(0, 0, 1) * UpwardMomentum;

		Mypawn->LaunchCharacter(AddForce,true,true);
	}
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

