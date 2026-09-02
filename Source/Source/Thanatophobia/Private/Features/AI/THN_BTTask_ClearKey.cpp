// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/AI/THN_BTTask_ClearKey.h"
#include "THN_BTTask_ClearKey.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTHN_BTTask_ClearKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	return EBTNodeResult::Succeeded;
}
