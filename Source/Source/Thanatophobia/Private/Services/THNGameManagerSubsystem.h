// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "THNGameManagerSubsystem.generated.h"

class ATHNExperimentationPuzzle;
class ATHNPlayerCharacter;
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IncubatorPuzzleComplete = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool OfficePuzzleComplete = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ExperimentationPuzzleComplete = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameStateChangedDelegate, EGameState, PreviousGameState, EGameState, NextGameState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameFlagsChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerKilledDelegate);

UCLASS()
class UTHNGameManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnGameStateChangedDelegate OnGameStateChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnGameFlagsChangedDelegate OnGameFlagsChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerKilledDelegate OnPlayerKilled;
	
	bool TrySwitchGameState(const EGameState& NewGameState);
	
	UFUNCTION(BlueprintCallable)
	FGameFlags GetGameFlags() const { return CurrentGameFlags; }
	EGameState GetCurrentGameState() const { return CurrentGameState; }
	
	UFUNCTION(BlueprintCallable)
	void KillPlayer();
	
	//These blueprint functions will need to be replaced once the incubator puzzle is updated
	UFUNCTION(BlueprintCallable)
	void RegisterIncubatorPuzzle(AActor* InIncubatorPuzzleActor);
	
	UFUNCTION(BlueprintCallable)
	void OnIncubatorPuzzleComplete();
	
	UFUNCTION(BlueprintCallable, Category="Debug")
	void Debug_ChangeGameFlags(FGameFlags NewGameFlags);
	
	void RegisterOfficePuzzle(ATHNDataPoisoningPuzzle* InOfficePuzzle);
	
	void RegisterPlayerCharacter(TObjectPtr<ATHNPlayerCharacter> Player);
	
	//Add later when this puzzle is made
	void RegisterExperimentationPuzzle(ATHNExperimentationPuzzle* InExperimentationPuzzle);
	
	UFUNCTION(BlueprintCallable)
	ATHNExperimentationPuzzle* GetExperimentationPuzzle() const { return ExperimentationPuzzle; }
	
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
	
	UPROPERTY()
	TObjectPtr<ATHNExperimentationPuzzle> ExperimentationPuzzle;
	
	UPROPERTY()
	TObjectPtr<ATHNPlayerCharacter> PlayerCharacter;
};
