// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THNDataPoisoningWidget.generated.h"

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
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, Category="UI")
	UTileView* WordTileView;
	
protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY()
	TArray<UTHNDataPoisoningWord*> Words;
};
