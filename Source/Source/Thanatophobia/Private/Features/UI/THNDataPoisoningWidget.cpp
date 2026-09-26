// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THNDataPoisoningWidget.h"

#include "THNDataPoisoningWord.h"
#include "Components/TileView.h"
#include "Components/WidgetComponent.h"
#include "Core/THNPuzzleManagerSubsystem.h"
#include "Features/Puzzles/THNDataPoisoningPuzzle.h"

void UTHNDataPoisoningWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	PuzzleManager = GetGameInstance()->GetSubsystem<UTHNPuzzleManagerSubsystem>();
	DataPoisoningPuzzle = PuzzleManager->GetDataPoisoningPuzzle();
	
	//WordTileView = CreateWidget<UTHNWordTileView>(this, WordTileViewBase);
	
	SelectWordsButton->OnClicked.AddDynamic(this, &UTHNDataPoisoningWidget::SelectWordsButtonClicked);
	
	for (int i = 0; i < DataPoisoningPuzzle->Settings.NumPages; i++)
	{
		WordTileViews.Add( WidgetTree->ConstructWidget<UTHNWordTileView>(WordTileViewBase));
		PageSwitcher->AddChild(WordTileViews[i]);
		
		for (int j = 0; j < DataPoisoningPuzzle->Settings.NumWordsPerPages; j++)
		{
			FName WordName = FName(FString("Word_").Append(FString::FromInt((DataPoisoningPuzzle->Settings.NumWordsPerPages * i) + j)));
			UTHNDataPoisoningWord* NewWord = WidgetTree->ConstructWidget<UTHNDataPoisoningWord>(UTHNDataPoisoningWord::StaticClass(), WordName);
			NewWord->WordIndex = (DataPoisoningPuzzle->Settings.NumWordsPerPages * i) + j;
			
			NewWord->BaseText = DataPoisoningPuzzle->Words[(DataPoisoningPuzzle->Settings.NumWordsPerPages * i) + j].Word;
			NewWord->Sentiment = DataPoisoningPuzzle->Words[(DataPoisoningPuzzle->Settings.NumWordsPerPages * i) + j].Sentiment;
		
			Words.Add(NewWord);
			WordTileViews[i]->WordTileView->AddItem(Words.Last());
		}
	}
}

void UTHNDataPoisoningWidget::ResetPuzzle()
{
	//Generate a new set of words to pull from
	DataPoisoningPuzzle->RefreshWordList();
		
	for (int i = 0; i < DataPoisoningPuzzle->Settings.NumPages; i++)
	{
		TArray<UTHNDataPoisoningWord*> NewWords;
			
		for (int j = 0; j < DataPoisoningPuzzle->Settings.NumWordsPerPages; j++)
		{
			//Update local word array with newly created word array from puzzle
			int ConvertedIndex = DataPoisoningPuzzle->Settings.NumWordsPerPages * i + j;
			Words[ConvertedIndex]->BaseText = DataPoisoningPuzzle->Words[ConvertedIndex].Word;
			Words[ConvertedIndex]->Sentiment = DataPoisoningPuzzle->Words[ConvertedIndex].Sentiment;
				
			//Update the text on the word widgets
			TArray<UUserWidget*> Widgets = WordTileViews[i]->WordTileView->GetDisplayedEntryWidgets();
			UTHNDataPoisoningWord* Word = Cast<UTHNDataPoisoningWord>(Widgets[j]);
			Word->BaseText = Words[ConvertedIndex]->BaseText;
			Word->Sentiment = Words[ConvertedIndex]->Sentiment;
			Word->UpdateWord();
		}
	}
		
	PageSwitcher->SetActiveWidgetIndex(0);
}

void UTHNDataPoisoningWidget::SelectWordsButtonClicked()
{
	if (PageSwitcher->GetActiveWidgetIndex() + 1 >= PageSwitcher->GetNumWidgets())
	{
		if (DataPoisoningPuzzle->CheckPuzzleCompletion())
		{
			DataPoisoningPuzzle->HandlePuzzleSucceeded();
		}
		else
		{
			ResetPuzzle();
		}
	}
	else
	{
		PageSwitcher->SetActiveWidgetIndex(PageSwitcher->GetActiveWidgetIndex() + 1);
	}
}
