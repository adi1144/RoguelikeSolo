// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;
class UParticleSystem;
UCLASS()
class ROGUELIKESOLO_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

protected:
	 
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* EffectComp;
	UPROPERTY(EditAnywhere)
		URadialForceComponent* RadialForce;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* ImpactVFX;
	// Called when the game starts or when spawned


	

public:	
	// Called every frame
	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



};
