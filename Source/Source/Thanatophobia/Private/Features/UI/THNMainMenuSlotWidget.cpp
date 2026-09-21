// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THNMainMenuSlotWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

UTHNMainMenuSlotWidget::UTHNMainMenuSlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetIsFocusable(true);
}
void UTHNMainMenuSlotWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock->SetText(ButtonText.IsEmpty() ? FText::FromString(TEXT("ButtonText")) : ButtonText);
}
void UTHNMainMenuSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnHovered.AddDynamic(this, &UTHNMainMenuSlotWidget::OnButtonHovered);
	Button->OnPressed.AddDynamic(this, &UTHNMainMenuSlotWidget::OnButtonPressedUpdated);

	SetHighlightState(false);
}

void UTHNMainMenuSlotWidget::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	OnFocused.Broadcast(this, true);

	Super::NativeOnAddedToFocusPath(InFocusEvent);
}

void UTHNMainMenuSlotWidget::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	OnFocused.Broadcast(this, false);

	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
}

void UTHNMainMenuSlotWidget::OnButtonHovered()
{
	Button->SetFocus();
}

void UTHNMainMenuSlotWidget::OnButtonPressedUpdated()
{
	OnPressed.Broadcast(this);
}


void UTHNMainMenuSlotWidget::SetHighlightState(bool bIsHighlighted)
{
	Border->SetBrushColor(bIsHighlighted ? BorderHighlightColor : FColor::Transparent);
}
