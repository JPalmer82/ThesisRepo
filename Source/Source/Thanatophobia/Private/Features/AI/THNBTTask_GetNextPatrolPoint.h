// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "THNBTTask_GetNextPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class UTHNBTTask_GetNextPatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UTHNBTTask_GetNextPatrolPoint();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
