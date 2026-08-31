// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "THNGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UTHNGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	//Called once at the start of the game, before any levels are loaded
	virtual void Init() override;
	
	// Called when the game is shutting down
	virtual void Shutdown() override;
};
