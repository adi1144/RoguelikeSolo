// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	HealthMax = 200.0f;


	Health = HealthMax;

	// ...
}


bool USAttributeComponent::IsAlive()
{
	
	return Health > 0.0f;
}



bool USAttributeComponent::ApplyHealthChange(float Delta)
{

	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	Health = NewHealth;
	

	OnHealthChange.Broadcast(nullptr, this, Health, Delta);

	return true;
}
float USAttributeComponent::GetHealt() 
{
	return Health;
}

float USAttributeComponent::GetHealtmax()
{
	return HealthMax;
}

