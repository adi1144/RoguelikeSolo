// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASPowerupActor::ASPowerupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(SphereComp);

	bIsActive = true;

	RespownTime = 10.f;

}

void ASPowerupActor::Interact_Implementation(APawn* InstigatorPawn)
{
	
}

void ASPowerupActor::ShowPowerUp()
{
	SetPowerUpState(true);
}

void ASPowerupActor::HideAndCooldownPowerUp()
{
	SetPowerUpState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ASPowerupActor::ShowPowerUp, RespownTime);


}

void ASPowerupActor::SetPowerUpState(bool bNewIsActive)
{
	bIsActive = bNewIsActive;

	OnRep_IsActive();
	
}

void ASPowerupActor::OnRep_IsActive()
{
	SetActorEnableCollision(bIsActive);
	RootComponent->SetVisibility(bIsActive, true);
}



