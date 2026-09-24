// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THNDataPoisoningWidget.h"

#include "THNDataPoisoningWord.h"
#include "Components/TileView.h"
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
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Words.Last()->BaseText);
			//WordTileView->AddItem(Words[i]);
		}
	}
}

void UTHNDataPoisoningWidget::SelectWordsButtonClicked()
{
	if (PageSwitcher->GetActiveWidgetIndex() + 1 >= PageSwitcher->GetNumWidgets())
	{
		UE_LOG(LogTemp, Warning, TEXT("THN: End of pages"));
	}
	else
	{
		PageSwitcher->SetActiveWidgetIndex(PageSwitcher->GetActiveWidgetIndex() + 1);
	}
}
