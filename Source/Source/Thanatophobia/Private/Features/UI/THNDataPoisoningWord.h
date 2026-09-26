// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Core/THNPuzzleManagerSubsystem.h"
#include "THNDataPoisoningWord.generated.h"

class ATHNDataPoisoningPuzzle;
/**
 * 
 */
UCLASS()
class UTHNDataPoisoningWord : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void UpdateWord();
	
	UPROPERTY(EditAnywhere, meta=(BindWidget), BlueprintReadWrite, Category="UI")
	TObjectPtr<UButton> WordButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget), BlueprintReadWrite, Category="UI")
	TObjectPtr<UTextBlock> WordTextBlock;
	
	UPROPERTY()
	FDataPoisoningWord Word;
	
	FString BaseText = "buh";
	int WordIndex = -1;
	FString Sentiment;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
private:
	UFUNCTION()
	void OnButtonClicked();
	
	UPROPERTY()
	TSoftObjectPtr<ATHNDataPoisoningPuzzle> DataPoisoningPuzzle;
	
	bool IsClicked = false;
	
	FButtonStyle BaseButtonStyle;
};
