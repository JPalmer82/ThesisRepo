// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THN_PauseMenuWidget.h"
#include "Features/UI/THN_MainMenuSlotWidget.h"
#include "Kismet/GameplayStatics.h"

void UTHN_PauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeSlot->OnFocused.AddUObject(this, &UTHN_PauseMenuWidget::OnSlotFocused);
	ResumeSlot->OnPressed.AddUObject(this, &UTHN_PauseMenuWidget::OnSlotPressed);
	ResumeSlot->SetFocus();

	MainMenuSlot->OnFocused.AddUObject(this, &UTHN_PauseMenuWidget::OnSlotFocused);
	MainMenuSlot->OnPressed.AddUObject(this, &UTHN_PauseMenuWidget::OnSlotPressed);
}

void UTHN_PauseMenuWidget::OnSlotFocused(UTHN_MainMenuSlotWidget* MenuSlot, bool bIsFocused)
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

void UTHN_PauseMenuWidget::OnSlotPressed(UTHN_MainMenuSlotWidget* MenuSlot)
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