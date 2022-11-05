// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPowerupActor.generated.h"


class USphereComponent;
class UStaticMeshComponent;

UCLASS(ABSTRACT)
class ROGUELIKESOLO_API ASPowerupActor : public AActor, public  ISGameplayInterface
{
	GENERATED_BODY()


protected:

	
		bool bIsActive;
	UFUNCTION()
		void OnRep_IsActive();

	UPROPERTY(EditAnywhere, Category="Components")
		USphereComponent* SphereComp;
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	

	UPROPERTY(EditAnywhere,Category="PowerUp")
	float RespownTime;

	FTimerHandle TimerHandle_RespawnTimer;

	UFUNCTION()
	void ShowPowerUp();

	void HideAndCooldownPowerUp();

	void SetPowerUpState(bool bNewIsActive);

	

	
	// Called when the game starts or when spawned
	
public:
	virtual  void Interact_Implementation(APawn* InstigatorPawn) override;

public:
	// Sets default values for this actor's properties
	ASPowerupActor();
};
