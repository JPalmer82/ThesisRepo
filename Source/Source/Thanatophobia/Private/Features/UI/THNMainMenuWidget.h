// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "THNMainMenuWidget.generated.h"

class UTHNMainMenuSlotWidget;
/**
 * 
 */
UCLASS()
class UTHNMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHNMainMenuSlotWidget> NewGameSlot;

	/*UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHNMainMenuSlotWidget> LoadGameSlot;*/

	/*UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHNMainMenuSlotWidget> SettingsSlot;*/

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHNMainMenuSlotWidget> QuitSlot;

	TObjectPtr<UTHNMainMenuSlotWidget> FocusedMainMenuSlot;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnSlotFocused(UTHNMainMenuSlotWidget* MainMenuSlot, bool bIsFocused);

	UFUNCTION()
	void OnSlotPressed(UTHNMainMenuSlotWidget* MainMenuSlot);
};
