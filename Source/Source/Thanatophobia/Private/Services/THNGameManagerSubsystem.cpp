// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/THNGameManagerSubsystem.h"

#include "Features/Puzzles/THNDataPoisoningPuzzle.h"

bool UTHNGameManagerSubsystem::TrySwitchGameState(const EGameState& NewGameState)
{
	//Add checks here if needed and return result
	SwitchGameState(NewGameState);
	return true;
}

void UTHNGameManagerSubsystem::RegisterIncubatorPuzzle(AActor* InIncubatorPuzzleActor)
{
	if (IncubatorPuzzle == nullptr)
	{
		IncubatorPuzzle = InIncubatorPuzzleActor;
		//IncubatorPuzzle->OnIncubatorPuzzleComplete.AddUniqueDynamic(this, &UTHNGameManagerSubsystem::OnIncubatorPuzzleComplete);
	}
}

void UTHNGameManagerSubsystem::OnIncubatorPuzzleComplete()
{
	CurrentGameFlags.IncubatorPuzzleComplete = true;
	OnGameFlagsChanged.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("OnDataPoisoningPuzzleComplete"));
}

void UTHNGameManagerSubsystem::RegisterOfficePuzzle(ATHNDataPoisoningPuzzle* InOfficePuzzle)
{
	if (OfficePuzzle == nullptr)
	{
		OfficePuzzle = InOfficePuzzle;
		OfficePuzzle->OnDataPoisoningPuzzleComplete.AddUniqueDynamic(this, &UTHNGameManagerSubsystem::OnDataPoisoningPuzzleComplete);
	}
}

void UTHNGameManagerSubsystem::SwitchGameState(EGameState NewGameState)
{
	CurrentGameState = NewGameState;
	OnGameStateChanged.Broadcast(CurrentGameState, NewGameState);
}

void UTHNGameManagerSubsystem::OnDataPoisoningPuzzleComplete()
{
	CurrentGameFlags.OfficePuzzleComplete = true;
	OnGameFlagsChanged.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("OnDataPoisoningPuzzleComplete"));
}
