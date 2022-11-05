// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"


class UParticleSystemComponent;
class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystem;

UCLASS()
class ROGUELIKESOLO_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectileBase();

protected:
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* ImpactVFX;
	UPROPERTY(EditAnywhere, Category = "Audio")
		UAudioComponent* FlySound;
	UPROPERTY(EditAnywhere, Category = "Audio")
		USoundBase* ExplodeSound;
	// Called when the game starts or when spawned

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly )
		float Damage;


	UFUNCTION()
		void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Explode();

public:	

	virtual void PostInitializeComponents() override;

};
