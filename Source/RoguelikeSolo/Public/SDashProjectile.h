// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKESOLO_API ASDashProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:
	ASDashProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float TeleportDelay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float DetonateDelay;


	FTimerHandle TimeHandler_DelayDetonate;

	UFUNCTION()
	//  void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) // ;
	void TeleportInstigator();
	 virtual void Explode_Implementation() override;

	virtual  void PostInitializeComponents() override;
};
