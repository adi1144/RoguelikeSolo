// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"
#include <Components/SphereComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASProjectileBase::ASProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASProjectileBase::OnActorOverlap);
	RootComponent=SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovmentComp");

	MovementComp->InitialSpeed = 1000.f;
	MovementComp->ProjectileGravityScale = 0.f;


	FlySound = CreateDefaultSubobject<UAudioComponent>("Audio");
	FlySound->SetupAttachment(RootComponent);


}

void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != GetInstigator())
	{
		Explode();
	}
	
	
}

void ASProjectileBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor!= GetInstigator())
	{
		USAttributeComponent* AttributeComp=Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));

		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-Damage);

			Explode();
		}
	}

}


void ASProjectileBase::Explode_Implementation()
{
	if (ensure(IsValid(this)))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(this, ExplodeSound, GetActorLocation(), GetActorRotation());
		Destroy();

	}
}


void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
}

