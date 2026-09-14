// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THN_MainMenuWidget.h"
#include "Features/UI/THN_MainMenuSlotWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UTHN_MainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NewGameSlot->OnFocused.AddUObject(this, &UTHN_MainMenuWidget::OnSlotFocused);
	NewGameSlot->OnPressed.AddUObject(this, &UTHN_MainMenuWidget::OnSlotPressed);
	NewGameSlot->SetFocus();

	/*LoadGameSlot->OnFocused.AddUObject(this, &UTHN_MainMenuWidget::OnSlotFocused);
	LoadGameSlot->OnPressed.AddUObject(this, &UTHN_MainMenuWidget::OnSlotPressed);*/ //For Load Game functionality later if we can

	/*SettingsSlot->OnFocused.AddUObject(this, &UTHN_MainMenuWidget::OnSlotFocused);
	SettingsSlot->OnPressed.AddUObject(this, &UTHN_MainMenuWidget::OnSlotPressed);*/ //For adjusting game settings later if we can

	QuitSlot->OnFocused.AddUObject(this, &UTHN_MainMenuWidget::OnSlotFocused);
	QuitSlot->OnPressed.AddUObject(this, &UTHN_MainMenuWidget::OnSlotPressed);
}

void UTHN_MainMenuWidget::OnSlotFocused(UTHN_MainMenuSlotWidget* MainMenuSlot, bool bIsFocused)
{
	if (bIsFocused)
	{
		if (FocusedMainMenuSlot)
		{
			FocusedMainMenuSlot->SetHighlightState(false);
		}

		FocusedMainMenuSlot = MainMenuSlot;
		if (FocusedMainMenuSlot)
		{
			FocusedMainMenuSlot->SetHighlightState(true);
		}
	}
	else if (MainMenuSlot)
	{
		MainMenuSlot->SetHighlightState(false);
	}
}

void UTHN_MainMenuWidget::OnSlotPressed(UTHN_MainMenuSlotWidget* MainMenuSlot)
{
	UWorld* World = GetWorld();

	if (MainMenuSlot == NewGameSlot)
	{
		if (World)
		{
			APlayerController* NewGamePlayerController = UGameplayStatics::GetPlayerController(World, 0);
			if (NewGamePlayerController)
			{
				// Switches input back to game controls and hide cursor
				FInputModeGameOnly InputMode;
				NewGamePlayerController->SetInputMode(InputMode);
				NewGamePlayerController->bShowMouseCursor = false;
			}
		}
		//Change the FName to whatever level will be the actual game level later
		UGameplayStatics::OpenLevel(GetWorld(), FName("ProgrammingZoo"));
	}
	else if (MainMenuSlot == QuitSlot)
	{
		//Quits the game
		UKismetSystemLibrary::QuitGame(World, UGameplayStatics::GetPlayerController(World, 0), EQuitPreference::Quit, true);
	}
}
