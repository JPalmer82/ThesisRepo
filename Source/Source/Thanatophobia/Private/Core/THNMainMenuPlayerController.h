// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "THNMainMenuPlayerController.generated.h"

class UTHNMainMenuWidget;
/**
 * 
 */
UCLASS()
class ATHNMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTHNMainMenuWidget> MainMenuClass;

	TObjectPtr<UTHNMainMenuWidget> MainMenu;

protected:
	virtual void BeginPlay() override;
};
