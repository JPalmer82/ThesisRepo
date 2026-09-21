// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THNMainMenuWidget.h"
#include "Features/UI/THNMainMenuSlotWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UTHNMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NewGameSlot->OnFocused.AddUObject(this, &UTHNMainMenuWidget::OnSlotFocused);
	NewGameSlot->OnPressed.AddUObject(this, &UTHNMainMenuWidget::OnSlotPressed);
	NewGameSlot->SetFocus();

	/*LoadGameSlot->OnFocused.AddUObject(this, &UTHN_MainMenuWidget::OnSlotFocused);
	LoadGameSlot->OnPressed.AddUObject(this, &UTHN_MainMenuWidget::OnSlotPressed);*/ //For Load Game functionality later if we can

	/*SettingsSlot->OnFocused.AddUObject(this, &UTHN_MainMenuWidget::OnSlotFocused);
	SettingsSlot->OnPressed.AddUObject(this, &UTHN_MainMenuWidget::OnSlotPressed);*/ //For adjusting game settings later if we can

	QuitSlot->OnFocused.AddUObject(this, &UTHNMainMenuWidget::OnSlotFocused);
	QuitSlot->OnPressed.AddUObject(this, &UTHNMainMenuWidget::OnSlotPressed);
}

void UTHNMainMenuWidget::OnSlotFocused(UTHNMainMenuSlotWidget* MainMenuSlot, bool bIsFocused)
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

void UTHNMainMenuWidget::OnSlotPressed(UTHNMainMenuSlotWidget* MainMenuSlot)
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
