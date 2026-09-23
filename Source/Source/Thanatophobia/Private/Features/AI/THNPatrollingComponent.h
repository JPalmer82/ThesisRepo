// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "THNPatrollingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTHNPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	AActor* GetNextPatrolPoint();

private:
	UPROPERTY(EditAnywhere, Category = "Patrolling")
	TArray<class ATargetPoint*> PatrolPoints;

	int NextPatrolPointIndex;
};
