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

	for (ATHNPossessableCharacter* Enemy : AIEnemies)
	{
		FHitResult hit;
		if (!GetWorld()->LineTraceSingleByChannel(hit, Enemy->GetActorLocation(), PlayerCharacter->GetActorLocation(), ECollisionChannel::ECC_Visibility))
		{
			DrawDebugLine(Enemy->GetWorld(), Enemy->GetActorLocation(), PlayerCharacter->GetActorLocation(), FColor::Green, false, 5.0f);
			float PathLength = (PlayerCharacter->GetActorLocation() - Enemy->GetActorLocation()).Length();
			if (PathLength < ClosestDist)
			{
				ClosestDist = PathLength;
				ClosestEnemy = Enemy;
			}
			UE_LOG(LogTemp, Warning, TEXT("%s had line of sight and was %.2f away from player"), *Enemy->GetName(), PathLength)
			continue;
		}
		else
		{
			DrawDebugLine(Enemy->GetWorld(), Enemy->GetActorLocation(), PlayerCharacter->GetActorLocation(), FColor::Red, false, 5.0f);
		}

		UNavigationPath* ResultPath = UNavigationSystemV1::FindPathToLocationSynchronously(Enemy->GetWorld(), Enemy->GetActorLocation(), PlayerCharacter->GetActorLocation());
		if (IsValid(ResultPath) && ResultPath->IsValid() && ResultPath->PathPoints.Num() > 0)
		{
			////DrawDebugString(GetWorld(), Enemy->GetActorLocation(), FString::Printf(TEXT("%.1f"), ResultPath->GetPathLength()), Enemy, FColor::Red, 5.0f);
			//for (int Index = 0; Index < ResultPath->PathPoints.Num() - 1; ++Index)//const auto& point : ResultPath->PathPoints)
			//{
			//	DrawDebugLine(Enemy->GetWorld(), ResultPath->PathPoints[Index], ResultPath->PathPoints[Index + 1], FColor::Yellow, false, 5.0f);
			//	float PointLength = (ResultPath->PathPoints[Index + 1] - ResultPath->PathPoints[Index]).Length();
			//	DrawDebugString(GetWorld(), ResultPath->PathPoints[Index], FString::Printf(TEXT("%.1f"), PointLength), nullptr, FColor::Red, 5.0f);
			//	//DrawDebugSphere(Enemy->GetWorld(), point, 20.0f, 8, FColor::Red, false, 5.0f, 200, 3.0f);
			//	//UE_LOG(LogTemp, Error, TEXT("%s"), *point.ToString())
			//}
			float PathLength = ResultPath->GetPathLength();
			UE_LOG(LogTemp, Error, TEXT("%s was %.2f away from player"), *Enemy->GetName(), PathLength)
			if (PathLength < ClosestDist)
			{
				ClosestDist = PathLength;
				ClosestEnemy = Enemy;
			}
		}

	}


	if (IsValid(ClosestEnemy) && ClosestEnemy->GetComponentByClass<UTHNPossessableActorComponent>()->bDoesDroneExist == false)
	{
		UE_LOG(LogTemp, Error, TEXT("%s was valid"), *ClosestEnemy->GetName())
		ClosestEnemy->GetComponentByClass<UTHNPossessableActorComponent>()->RandomizePossessionPosition();

		if (IsValid(LastActivated))
		{
			DeactivatePreviousEnemy();
		}

		LastActivated = ClosestEnemy;
	}
}

void UTHNAIManagerSubsystem::DeactivatePreviousEnemy()
{
	if (IsValid(LastActivated))
	{
		LastActivated->GetComponentByClass<UTHNPossessableActorComponent>()->ClearPossessionPositions();
		LastActivated = nullptr;
	}
}
