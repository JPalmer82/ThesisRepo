// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "THNGameInstance.generated.h"


//Change to struct/class
UENUM()
enum class EGameState
{
	Default,
	Puzzle,
	Paused
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameStateChangedDelegate, EGameState, PreviousGameState, EGameState, NextGameState);

UCLASS()
class UTHNGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	//Called once at the start of the game, before any levels are loaded
	virtual void Init() override;
	
	// Called when the game is shutting down
	virtual void Shutdown() override;
	
	FOnGameStateChangedDelegate OnGameStateChangedDelegate;
	EGameState GetCurrentGameState() const { return CurrentGameState; }
	bool TrySwitchGameState(const EGameState& NewGameState);
	
private:
	EGameState CurrentGameState = EGameState::Default;
	
	void SwitchGameState(EGameState NewGameState);
};
