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
	float ClosestDist = 0;
	ATHNPossessableCharacter* ClosestEnemy = nullptr;

	for (ATHNPossessableCharacter* Enemy : AIEnemies)
	{
		float PathLength = 0;
		UNavigationPath* ResultPath = UNavigationSystemV1::FindPathToLocationSynchronously(Enemy, Enemy->GetActorLocation(), PlayerCharacter->GetActorLocation());
		if (IsValid(ResultPath))
		{
			PathLength = ResultPath->GetPathLength();
		}

		if (ClosestDist <= PathLength)
		{
			ClosestDist = PathLength;
			ClosestEnemy = Enemy;
		}
	}

	if (IsValid(ClosestEnemy))
	{
		ClosestEnemy->GetComponentByClass<UTHNPossessableActorComponent>()->RandomizePossessionPosition();
	}
}
