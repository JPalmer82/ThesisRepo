// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "THN_MainMenuWidget.generated.h"

class UTHN_MainMenuSlotWidget;
/**
 * 
 */
UCLASS()
class UTHN_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHN_MainMenuSlotWidget> NewGameSlot;

	/*UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHN_MainMenuSlotWidget> LoadGameSlot;*/

	/*UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHN_MainMenuSlotWidget> SettingsSlot;*/

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHN_MainMenuSlotWidget> QuitSlot;

	TObjectPtr<UTHN_MainMenuSlotWidget> FocusedMainMenuSlot;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnSlotFocused(UTHN_MainMenuSlotWidget* MainMenuSlot, bool bIsFocused);

	UFUNCTION()
	void OnSlotPressed(UTHN_MainMenuSlotWidget* MainMenuSlot);
};
