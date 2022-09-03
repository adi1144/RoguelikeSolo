// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ASDashProjectile::ASDashProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComp->InitialSpeed = 6000.f;
	SphereComp->SetCollisionProfileName("Projectile");

	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;


}

void ASDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimeHandler_DelayDetonate);

	MovementComp->StopMovementImmediately();
	FTimerHandle TimerHandle_TeleportTime;

	GetWorldTimerManager().SetTimer(TimerHandle_TeleportTime, this, &ASDashProjectile::TeleportInstigator, TeleportDelay);


	
}

void ASDashProjectile::TeleportInstigator()
{

	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{

		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);



	}

	Destroy();
}





void ASDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
//	SphereComp->OnComponentHit.AddDynamic(this, &ASDashProjectile::OnActorHit);
	GetWorldTimerManager().SetTimer(TimeHandler_DelayDetonate, this, &ASDashProjectile::Explode, DetonateDelay);
	
}


