// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "THNGameManagerSubsystem.generated.h"

class ATHNDataPoisoningPuzzle;

UENUM()
enum class EGameState
{
	Default,
	Puzzle,
	Paused
};

USTRUCT(BlueprintType)
struct FGameFlags
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	bool IncubatorPuzzleComplete = false;
	
	UPROPERTY(BlueprintReadOnly)
	bool OfficePuzzleComplete = false;
	
	UPROPERTY(BlueprintReadOnly)
	bool ExperimentationPuzzleComplete = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameStateChangedDelegate, EGameState, PreviousGameState, EGameState, NextGameState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameFlagsChangedDelegate);

UCLASS()
class UTHNGameManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	FOnGameStateChangedDelegate OnGameStateChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnGameFlagsChangedDelegate OnGameFlagsChanged;
	
	bool TrySwitchGameState(const EGameState& NewGameState);
	
	UFUNCTION(BlueprintCallable)
	FGameFlags GetGameFlags() const { return CurrentGameFlags; }
	EGameState GetCurrentGameState() const { return CurrentGameState; }
	
	
	//These blueprint functions will need to be replaced once the incubator puzzle is updated
	UFUNCTION(BlueprintCallable)
	void RegisterIncubatorPuzzle(AActor* InIncubatorPuzzleActor);
	
	UFUNCTION(BlueprintCallable)
	void OnIncubatorPuzzleComplete();
	
	void RegisterOfficePuzzle(ATHNDataPoisoningPuzzle* InOfficePuzzle);
	
	//Add later when this puzzle is made
	//void RegisterExperimentationPuzzle(ATHNExperimentationPuzzle* ExperimentationPuzzle);
	
private:
	EGameState CurrentGameState = EGameState::Default;
	
	void SwitchGameState(EGameState NewGameState);
	
	UFUNCTION()
	void OnDataPoisoningPuzzleComplete();
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameFlags CurrentGameFlags;
	
	UPROPERTY()
	TObjectPtr<AActor> IncubatorPuzzle;
	
	UPROPERTY()
	TObjectPtr<ATHNDataPoisoningPuzzle> OfficePuzzle;
};
