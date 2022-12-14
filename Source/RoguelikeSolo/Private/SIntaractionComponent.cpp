// Fill out your copyright notice in the Description page of Project Settings.


#include "SIntaractionComponent.h"

#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USIntaractionComponent::USIntaractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void USIntaractionComponent::PrimaryInteract()
{
	TArray<struct FHitResult> Hits;

	FVector EyeLocation;
	FRotator EyeRotation;

	

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	float Radius = 30.0f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);


	AActor* MyOwner = GetOwner();

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector()* 1000.f);

	bool BlockHit= GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);


	FColor LineColor = BlockHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit: Hits)
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor)
		{
			if (HitActor->Implements<USGameplayInterface>())
			{

				APawn* MyPawn = Cast<APawn>(MyOwner);

				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);

				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius,32, LineColor, false, 2.0f);
				break;
				
			}



		}
		
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);


}



// Called when the game starts
void USIntaractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USIntaractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

