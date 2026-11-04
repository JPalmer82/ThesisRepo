// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/THNGameManagerSubsystem.h"

#include "Core/THNCameraManagerSubsystem.h"
#include "Features/Characters/THNPlayerCharacter.h"
#include "Features/Puzzles/THNDataPoisoningPuzzle.h"
#include "Features/Puzzles/THNExperimentationPuzzle.h"

void UTHNGameManagerSubsystem::SwitchGameState(EGameState NewGameState)
{
	CurrentGameState = NewGameState;
	OnGameStateChanged.Broadcast(CurrentGameState, NewGameState);
}

bool UTHNGameManagerSubsystem::TrySwitchGameState(const EGameState& NewGameState)
{
	//Add checks here if needed and return result
	SwitchGameState(NewGameState);
	return true;
}

void UTHNGameManagerSubsystem::KillPlayer()
{
	PlayerCharacter = nullptr;
	ExperimentationPuzzle = nullptr;
	OfficePuzzle = nullptr;
	IncubatorPuzzle = nullptr;
	
	TrySwitchGameState(EGameState::Default);
	CurrentGameFlags = FGameFlags();
	OnPlayerKilled.Broadcast();
}

void UTHNGameManagerSubsystem::RegisterIncubatorPuzzle(AActor* InIncubatorPuzzleActor)
{
	if (IncubatorPuzzle == nullptr)
	{
		IncubatorPuzzle = InIncubatorPuzzleActor;
		//IncubatorPuzzle->OnIncubatorPuzzleComplete.AddUniqueDynamic(this, &UTHNGameManagerSubsystem::OnIncubatorPuzzleComplete);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("THN: %s is already registered"), *InIncubatorPuzzleActor->GetName());
	}
}

void UTHNGameManagerSubsystem::RegisterOfficePuzzle(ATHNDataPoisoningPuzzle* InOfficePuzzle)
{
	if (OfficePuzzle == nullptr)
	{
		OfficePuzzle = InOfficePuzzle;
		OfficePuzzle->OnDataPoisoningPuzzleComplete.AddUniqueDynamic(this, &UTHNGameManagerSubsystem::OnDataPoisoningPuzzleComplete);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("THN: %s is already registered"), *InOfficePuzzle->GetName());
	}
}

void UTHNGameManagerSubsystem::RegisterPlayerCharacter(TObjectPtr<ATHNPlayerCharacter> Player)
{
	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = Player;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("THN: %s is already registered"), *Player->GetName());
	}
}

void UTHNGameManagerSubsystem::RegisterExperimentationPuzzle(ATHNExperimentationPuzzle* InExperimentationPuzzle)
{
	if (ExperimentationPuzzle == nullptr)
	{
		ExperimentationPuzzle = InExperimentationPuzzle;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("THN: %s is already registered"), *InExperimentationPuzzle->GetName());
	}
}

void UTHNGameManagerSubsystem::OnIncubatorPuzzleComplete()
{
	if (!CurrentGameFlags.IncubatorPuzzleComplete)
	{
		CurrentGameFlags.IncubatorPuzzleComplete = true;
		OnGameFlagsChanged.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("OnDataPoisoningPuzzleComplete"));
	}
}

void UTHNGameManagerSubsystem::Debug_ChangeGameFlags(FGameFlags NewGameFlags)
{
	CurrentGameFlags = NewGameFlags;
	OnGameFlagsChanged.Broadcast();
}

void UTHNGameManagerSubsystem::OnDataPoisoningPuzzleComplete()
{
	if (!CurrentGameFlags.OfficePuzzleComplete)
	{
		CurrentGameFlags.OfficePuzzleComplete = true;
		OnGameFlagsChanged.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("OnDataPoisoningPuzzleComplete"));
	}
}
