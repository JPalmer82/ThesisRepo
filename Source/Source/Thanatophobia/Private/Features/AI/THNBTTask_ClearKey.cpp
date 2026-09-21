// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/AI/THNBTTask_ClearKey.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTHNBTTask_ClearKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	return EBTNodeResult::Succeeded;
}
