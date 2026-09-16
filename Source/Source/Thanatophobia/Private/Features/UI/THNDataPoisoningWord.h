// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "THNDataPoisoningWord.generated.h"

/**
 * 
 */
UCLASS()
class UTHNDataPoisoningWord : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, Category="UI")
	UButton* WordButton;
	
protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void OnButtonClicked();
};
