// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/THN_MainMenuPlayerController.h"
#include "Features/UI/THN_MainMenuWidget.h"

void ATHN_MainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);

	MainMenu = CreateWidget<UTHN_MainMenuWidget>(GetWorld(), MainMenuClass);
	checkf(MainMenu, TEXT("THN - Failed To Create MainMenu!!!"))
	MainMenu->AddToViewport();
}
