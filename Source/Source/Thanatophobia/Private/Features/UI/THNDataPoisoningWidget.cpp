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
	
	for (int i = 0; i < DataPoisoningPuzzle->Settings.NumWordsPerPages; i++)
	{
		FName WordName = FName(FString("Word_").Append(FString::FromInt(i)));
		UTHNDataPoisoningWord* NewWord = WidgetTree->ConstructWidget<UTHNDataPoisoningWord>(UTHNDataPoisoningWord::StaticClass(), WordName);
		Words.Add(NewWord);
		WordTileView->AddItem(Words[i]);
	}
}
