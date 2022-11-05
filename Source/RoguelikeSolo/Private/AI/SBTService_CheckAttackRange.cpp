// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (ensure(Blackboard))
	{
		AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject("TargetActor"));

		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();

			if (ensure(MyController))
			{

				APawn* AIPawn = MyController->GetPawn();

				if (ensure(AIPawn))
				{
					float Distance = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithInRange = Distance < 2000.f;

					bool bHasLOS = false;

					if (bWithInRange)
					{
						bHasLOS = MyController->LineOfSightTo(TargetActor);
					}
					 

					Blackboard->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithInRange && bHasLOS));
				}

			}

		}


	}
}
