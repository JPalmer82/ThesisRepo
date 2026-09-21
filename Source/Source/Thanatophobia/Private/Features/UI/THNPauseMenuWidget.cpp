// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THNPauseMenuWidget.h"
#include "Features/UI/THNMainMenuSlotWidget.h"
#include "Kismet/GameplayStatics.h"

void UTHNPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeSlot->OnFocused.AddUObject(this, &UTHNPauseMenuWidget::OnSlotFocused);
	ResumeSlot->OnPressed.AddUObject(this, &UTHNPauseMenuWidget::OnSlotPressed);
	ResumeSlot->SetFocus();

	MainMenuSlot->OnFocused.AddUObject(this, &UTHNPauseMenuWidget::OnSlotFocused);
	MainMenuSlot->OnPressed.AddUObject(this, &UTHNPauseMenuWidget::OnSlotPressed);
}

void UTHNPauseMenuWidget::OnSlotFocused(UTHNMainMenuSlotWidget* MenuSlot, bool bIsFocused)
{
	if (bIsFocused)
	{
		if (FocusedMenuSlot)
		{
			FocusedMenuSlot->SetHighlightState(false);
		}

		FocusedMenuSlot = MenuSlot;
		if (FocusedMenuSlot)
		{
			FocusedMenuSlot->SetHighlightState(true);
		}
	}
	else if (MenuSlot)
	{
		MainMenuSlot->SetHighlightState(false);
	}
}

void UTHNPauseMenuWidget::OnSlotPressed(UTHNMainMenuSlotWidget* MenuSlot)
{
	UWorld* World = GetWorld();
	APlayerController* NewGamePlayerController = UGameplayStatics::GetPlayerController(World, 0);

	if (MenuSlot == ResumeSlot)
	{
		//Unpauses game
		UGameplayStatics::SetGamePaused(World, false);

		//resets input
		FInputModeGameOnly InputMode;
		NewGamePlayerController->SetInputMode(InputMode);
		NewGamePlayerController->bShowMouseCursor = false;

		//removes pause menu widget from screen
		RemoveFromParent();
	}
	else if (MenuSlot == MainMenuSlot)
	{
		//Returns to MainMenu
		UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuLevel"));
	}
}