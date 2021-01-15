// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LaunchPad.generated.h"


class UBoxComponent;

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UBoxComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	float ForwardMomentum;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	float UpwardMomentum;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UParticleSystem* LaunchParticle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
