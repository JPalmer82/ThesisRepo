// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THN_MainMenuSlotWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

UTHN_MainMenuSlotWidget::UTHN_MainMenuSlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetIsFocusable(true);
}
void UTHN_MainMenuSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock->SetText(ButtonText.IsEmpty() ? FText::FromString(TEXT("ButtonText")) : ButtonText);
}
void UTHN_MainMenuSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnHovered.AddDynamic(this, &UTHN_MainMenuSlotWidget::OnButtonHovered);
	Button->OnPressed.AddDynamic(this, &UTHN_MainMenuSlotWidget::OnButtonPressedUpdated);

	SetHighlightState(false);
}

void UTHN_MainMenuSlotWidget::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	OnFocused.Broadcast(this, true);

	Super::NativeOnAddedToFocusPath(InFocusEvent);
}

void UTHN_MainMenuSlotWidget::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	OnFocused.Broadcast(this, false);

	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
}

void UTHN_MainMenuSlotWidget::OnButtonHovered()
{
	Button->SetFocus();
}

void UTHN_MainMenuSlotWidget::OnButtonPressedUpdated()
{
	OnPressed.Broadcast(this);
}


void UTHN_MainMenuSlotWidget::SetHighlightState(bool bIsHighlighted)
{
	Border->SetBrushColor(bIsHighlighted ? BorderHighlightColor : FColor::Transparent);
}
