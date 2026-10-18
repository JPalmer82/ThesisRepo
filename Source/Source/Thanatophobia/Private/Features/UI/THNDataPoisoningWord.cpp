// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THNDataPoisoningWord.h"

#include "THNDataPoisoningWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Core/THNPuzzleManagerSubsystem.h"
#include "Features/Puzzles/THNDataPoisoningPuzzle.h"

void UTHNDataPoisoningWord::UpdateWord()
{
	WordTextBlock->SetText(FText::FromString(BaseText));
	WordButton->SetStyle(BaseButtonStyle);
	IsClicked = false;
}

void UTHNDataPoisoningWord::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	WordIndex = Cast<UTHNDataPoisoningWord>(ListItemObject)->WordIndex;
	BaseText = Cast<UTHNDataPoisoningWord>(ListItemObject)->BaseText;
	Sentiment = Cast<UTHNDataPoisoningWord>(ListItemObject)->Sentiment;
	WordTextBlock->SetText(FText::FromString(BaseText));
}

void UTHNDataPoisoningWord::NativeConstruct()
{
	Super::NativeConstruct();
	
	WordButton->OnClicked.AddDynamic(this, &UTHNDataPoisoningWord::OnButtonClicked);
	DataPoisoningPuzzle = GetGameInstance()->GetSubsystem<UTHNPuzzleManagerSubsystem>()->GetDataPoisoningPuzzle();
	BaseButtonStyle = WordButton->GetStyle();
}

void UTHNDataPoisoningWord::OnButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Sentiment);
	DataPoisoningPuzzle->SelectWord(this);
	FButtonStyle NewStyle = BaseButtonStyle;
	
	if (IsClicked)
	{
		NewStyle.Normal.TintColor = FSlateColor(FColor(122, 255, 122, 0));
		WordButton->SetStyle(NewStyle);
		IsClicked = !IsClicked;
	}
	else
	{
		NewStyle.Normal.TintColor = FSlateColor(FColor(122, 200, 122, 255));
		WordButton->SetStyle(NewStyle);
		IsClicked = !IsClicked;
	}
}
