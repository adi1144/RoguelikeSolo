// Fill out your copyright notice in the Description page of Project Settings.

#include "SPlayerCharacter.h"
#include "SIntaractionComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/Character.h>
#include <GameFramework\CharacterMovementComponent.h>
#include <Math/RotationMatrix.h>
#include "SAttributeComponent.h"



// Sets default values
ASPlayerCharacter::ASPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp=CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp=CreateDefaultSubobject<UCameraComponent>("CamperaComp");
	CameraComp->SetupAttachment(SpringArmComp);


	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	AttackAnim = CreateDefaultSubobject<UAnimMontage>("AttackAnim");
	
	
	InteractionComp = CreateDefaultSubobject<USIntaractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");


}

void ASPlayerCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void ASPlayerCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightRotation = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightRotation, Value);
}

void ASPlayerCharacter::PrimaryInteraction()
{
	InteractionComp->PrimaryInteract();
	
}


void ASPlayerCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	

	GetWorldTimerManager().SetTimer(AttackTimer,this, &ASPlayerCharacter::PrimayAtttack_TimeElapsed,  0.2f);
}

void ASPlayerCharacter::PrimayAtttack_TimeElapsed()
{

	SpawnProjectile(ProjectileClass);
	


}
void ASPlayerCharacter::BlackHole()
{
	SpawnProjectile(BlackHoleClass);
}


void ASPlayerCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn))
	{
		
	
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FHitResult Hit;
	FVector TraceStart;
	FVector TraceEnd;

	FCollisionShape Shape;
	Shape.SetSphere(20.0f);

	TraceStart = CameraComp->GetComponentLocation();
	TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjParams.AddObjectTypesToQuery(ECC_Pawn);

	FRotator ProjRotation;

	if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
	{
		ProjRotation = FRotationMatrix::MakeFromX(Hit.ImpactPoint - HandLocation).Rotator();
	}
	else
	{
		ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
	}
	
	FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
	GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);


	}

		


}
void ASPlayerCharacter::Dash()
{
	SpawnProjectile(DashProjectile);
}


void ASPlayerCharacter::OnHealtChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth<=0.f && Delta<0)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());

		DisableInput(PC);
	}
	if (Delta < 0)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}

}

void ASPlayerCharacter::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}



// Called when the game starts or when spawned
void ASPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChange.AddDynamic(this, &ASPlayerCharacter::OnHealtChange);
	
}

// Called every frame
void ASPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASPlayerCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASPlayerCharacter::PrimaryInteraction);
	PlayerInputComponent->BindAction("BlackHole", IE_Pressed, this, &ASPlayerCharacter::BlackHole);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ASPlayerCharacter::Dash);
}

