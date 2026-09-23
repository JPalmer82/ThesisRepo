// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/AI/THNBTTask_GetNextPatrolPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Features/AI/THNPatrollingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UTHNBTTask_GetNextPatrolPoint::UTHNBTTask_GetNextPatrolPoint()
{
	NodeName = "GetNextPatrolPoint";
}

EBTNodeResult::Type UTHNBTTask_GetNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* OwnerAIC = OwnerComp.GetAIOwner();
	if (!OwnerAIC)
	{
		return EBTNodeResult::Failed;
	}

	UTHNPatrollingComponent* PatrollingComp = OwnerAIC->GetPawn()->GetComponentByClass<UTHNPatrollingComponent>();
	if (!PatrollingComp)
	{
		return EBTNodeResult::Failed;
	}

	AActor* NextPatrolPoint = PatrollingComp->GetNextPatrolPoint();
	UBlackboardComponent* OwnerBlackboardComp = OwnerComp.GetBlackboardComponent();
	OwnerBlackboardComp->SetValueAsObject(GetSelectedBlackboardKey(), NextPatrolPoint);

	return EBTNodeResult::Succeeded;
}
