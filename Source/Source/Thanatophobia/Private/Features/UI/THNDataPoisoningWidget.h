// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "THNWordTileView.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "THNDataPoisoningWidget.generated.h"

class ATHNDataPoisoningPuzzle;
class UTHNPuzzleManagerSubsystem;
class UTHNDataPoisoningWord;
class UTileView;
/**
 * 
 */
UCLASS()
class UTHNDataPoisoningWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTHNWordTileView> WordTileViewBase;
	
	//UPROPERTY(meta=(BindWidget), BlueprintReadWrite, Category="UI")
	UPROPERTY()
	TArray<TObjectPtr<UTHNWordTileView>> WordTileViews;
	
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, Category="UI")
	TObjectPtr<UWidgetSwitcher> PageSwitcher;
	
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, Category="UI")
	TObjectPtr<UButton> SelectWordsButton;
	
	//bool Initialize(int WordsPerPage, int NumPages);
	//virtual void NativeOnInitialized() override;
	
protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY()
	TArray<UTHNDataPoisoningWord*> Words;
	
	UPROPERTY()
	TSoftObjectPtr<UTHNPuzzleManagerSubsystem> PuzzleManager;
	
	UPROPERTY()
	TSoftObjectPtr<ATHNDataPoisoningPuzzle> DataPoisoningPuzzle;
	
	UFUNCTION()
	void SelectWordsButtonClicked();
};
