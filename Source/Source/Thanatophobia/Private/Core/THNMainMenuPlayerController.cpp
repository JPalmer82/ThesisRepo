// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/THNMainMenuPlayerController.h"
#include "Features/UI/THNMainMenuWidget.h"

void ATHNMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);

	MainMenu = CreateWidget<UTHNMainMenuWidget>(GetWorld(), MainMenuClass);
	checkf(MainMenu, TEXT("THN - Failed To Create MainMenu!!!"))
	MainMenu->AddToViewport();
}
