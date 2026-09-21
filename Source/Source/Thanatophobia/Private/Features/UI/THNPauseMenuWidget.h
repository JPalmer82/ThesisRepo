// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "THNPauseMenuWidget.generated.h"

class UTHNMainMenuSlotWidget;
/**
 * 
 */
UCLASS()
class UTHNPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHNMainMenuSlotWidget> ResumeSlot;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTHNMainMenuSlotWidget> MainMenuSlot;

	TObjectPtr<UTHNMainMenuSlotWidget> FocusedMenuSlot;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnSlotFocused(UTHNMainMenuSlotWidget* MenuSlot, bool bIsFocused);

	UFUNCTION()
	void OnSlotPressed(UTHNMainMenuSlotWidget* MenuSlot);
};
