// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STargetDummy.generated.h"

class USAttributeComponent;
UCLASS()
class ROGUELIKESOLO_API ASTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTargetDummy();

protected:

	UPROPERTY(EditAnywhere, Category = "Attributes")
		USAttributeComponent* AttributeComp;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;


	UFUNCTION()
	void OnHealtChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
