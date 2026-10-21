// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/THNAIManagerSubsystem.h"
#include "Features/NPCs/THNPossessableActorComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "THNAIManagerSubsystem.h"

void UTHNAIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UTHNAIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UTHNAIManagerSubsystem::ActivateClosestEnemy()
{
	float ClosestDist = MAX_FLT;
	ATHNPossessableCharacter* ClosestEnemy = nullptr;

	for (ATHNPossessableCharacter* Enemy : AIEnemies)
	{
		UNavigationPath* ResultPath = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), Enemy->GetActorLocation(), PlayerCharacter->GetActorLocation());
		if (IsValid(ResultPath) && ResultPath->IsValid() && ResultPath->PathPoints.Num() > 0)
		{
			float PathLength = ResultPath->GetPathLength();
			UE_LOG(LogTemp, Error, TEXT("%s was %.2f away from player"), *Enemy->GetName(), PathLength)
			if (PathLength < ClosestDist)
			{
				ClosestDist = PathLength;
				ClosestEnemy = Enemy;
				UE_LOG(LogTemp, Error, TEXT(">> New closest enemy found: %s with distance %.2f"), *Enemy->GetName(), PathLength)
			}
		}

	}

	if (IsValid(ClosestEnemy) && ClosestEnemy->GetComponentByClass<UTHNPossessableActorComponent>()->bDoesDroneExist == false)
	{
		ClosestEnemy->GetComponentByClass<UTHNPossessableActorComponent>()->RandomizePossessionPosition();
	}
}
