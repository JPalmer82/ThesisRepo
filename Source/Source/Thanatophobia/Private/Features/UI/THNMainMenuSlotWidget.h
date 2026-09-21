// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "THNMainMenuSlotWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMainMenuSlotFocusedEvent, UTHNMainMenuSlotWidget* MainMenuSlot, bool bIsFocused);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMainMenuSlotPressedEvent, UTHNMainMenuSlotWidget* MainMenuSlot);

class UBorder;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class UTHNMainMenuSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UBorder> Border;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UButton> Button;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTextBlock> TextBlock;

	UPROPERTY(meta = (ExposeOnSpawn), EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText ButtonText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	FColor BorderHighlightColor = FColor::White;

public:
	FOnMainMenuSlotFocusedEvent OnFocused;
	FOnMainMenuSlotPressedEvent OnPressed;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;

	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonPressedUpdated();

public:
	UTHNMainMenuSlotWidget(const FObjectInitializer& ObjectInitializer);

	void SetHighlightState(bool bIsHighlighted);
};
