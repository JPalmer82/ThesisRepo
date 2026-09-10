// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/THNGameInstance.h"

void UTHNGameInstance::Init()
{
	Super::Init();
}

void UTHNGameInstance::Shutdown()
{
	Super::Shutdown();
}

bool UTHNGameInstance::TrySwitchGameState(const EGameState& NewGameState)
{
	//Add checks here if needed and return result
	SwitchGameState(NewGameState);
	return true;
}

void UTHNGameInstance::SwitchGameState(EGameState NewGameState)
{
	OnGameStateChangedDelegate.Broadcast(CurrentGameState, NewGameState);
	CurrentGameState = NewGameState;
}
