// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THNExperimentationWidget.h"

#include "Components/WidgetComponent.h"
#include "Features/Puzzles/THNExperimentationPuzzle.h"
#include "Services/THNGameManagerSubsystem.h"

void UTHNExperimentationWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (UTHNGameManagerSubsystem* GameManger = GetGameInstance()->GetSubsystem<UTHNGameManagerSubsystem>())
	{
		if (ATHNExperimentationPuzzle* Puzzle = GameManger->GetExperimentationPuzzle())
		{
			if (UTextureRenderTarget2D* buh = Puzzle->GetWidgetRenderTarget())
			{
				UE_LOG(LogTemp, Error, TEXT("SUCCESSFULLY INITIALIZED WIDGET"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("COULD NOT GET RENDER TARGET"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("COULD NOT GET PUZZLE"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("COULD NOT GET GAME MANAGER"));
	}
}
