// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "THN_MainMenuPlayerController.generated.h"

class UTHN_MainMenuWidget;
/**
 * 
 */
UCLASS()
class ATHN_MainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTHN_MainMenuWidget> MainMenuClass;

	TObjectPtr<UTHN_MainMenuWidget> MainMenu;

protected:
	virtual void BeginPlay() override;
};
