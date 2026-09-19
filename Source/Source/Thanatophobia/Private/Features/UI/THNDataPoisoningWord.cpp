// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THNDataPoisoningWord.h"

#include "Blueprint/WidgetTree.h"

void UTHNDataPoisoningWord::UpdateText(const ANSICHAR* text) const
{
	WordTextBlock->SetText(FText::FromString(BaseText));
}

void UTHNDataPoisoningWord::NativeConstruct()
{
	Super::NativeConstruct();
	
	WordButton->OnClicked.AddDynamic(this, &UTHNDataPoisoningWord::OnButtonClicked);
	
	//WordTextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), "WordText");
	WordTextBlock->SetText(FText::FromString(BaseText));
}

void UTHNDataPoisoningWord::OnButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Clicked"), *GetName());
}
