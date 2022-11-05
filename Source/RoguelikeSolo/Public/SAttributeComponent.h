// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChange, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKESOLO_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Attributes")
		float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
		float HealthMax;

public:


	UPROPERTY(BlueprintAssignable)
		FOnHealthChange OnHealthChange;

	UFUNCTION(BlueprintCallable)
	bool IsAlive();
	UFUNCTION(BlueprintCallable,Category="Attributes")
	bool ApplyHealthChange(float Delta);

	UFUNCTION(BlueprintCallable)
		float GetHealt();
	UFUNCTION(BlueprintCallable)
		float GetHealtmax();
	// Called every frame
	
};
