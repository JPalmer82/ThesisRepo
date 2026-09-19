// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "THNDataPoisoningWord.generated.h"

/**
 * 
 */
UCLASS()
class UTHNDataPoisoningWord : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	void UpdateText(const ANSICHAR* text) const;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget), BlueprintReadWrite, Category="UI")
	TObjectPtr<UButton> WordButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget), BlueprintReadWrite, Category="UI")
	TObjectPtr<UTextBlock> WordTextBlock;
	
	FString BaseText = "buh";
	
protected:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void OnButtonClicked();
};
