// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "THN_PauseMenuWidget.generated.h"

class UTHN_MainMenuSlotWidget;
/**
 * 
 */
UCLASS()
class UTHN_PauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHN_MainMenuSlotWidget> ResumeSlot;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHN_MainMenuSlotWidget> MainMenuSlot;

	TObjectPtr<UTHN_MainMenuSlotWidget> FocusedMenuSlot;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnSlotFocused(UTHN_MainMenuSlotWidget* MenuSlot, bool bIsFocused);

	UFUNCTION()
	void OnSlotPressed(UTHN_MainMenuSlotWidget* MenuSlot);
};
