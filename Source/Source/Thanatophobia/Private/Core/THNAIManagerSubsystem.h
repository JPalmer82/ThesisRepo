// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Features/Characters/THNPlayerCharacter.h"
#include "Features/NPCs/THNPossessableCharacter.h"

#include "THNAIManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UTHNAIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Character")
	ATHNPlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Enemies")
	TArray<TObjectPtr<ATHNPossessableCharacter>> AIEnemies;
};
