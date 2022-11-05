// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPlayerCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class ASMagicProjectile;
class USIntaractionComponent;
class USAttributeComponent;
UCLASS()
class ROGUELIKESOLO_API ASPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

		

public:
	

	// Sets default values for this character's properties
	ASPlayerCharacter();
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BlackHoleClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> DashProjectile;
protected:
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere)
		UAnimMontage* AttackAnim;
	UPROPERTY(EditAnywhere)
		USIntaractionComponent* InteractionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USAttributeComponent* AttributeComp;

	FTimerHandle AttackTimer;

	// Called when the game starts or when spawned

	void MoveForward(float Value);
	void MoveRight( float Value);
	void PrimaryInteraction();
	void PrimaryAttack();
	void PrimayAtttack_TimeElapsed();
	void Dash();
	void BlackHole();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	UFUNCTION()
	void OnHealtChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
	UFUNCTION()
		void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
