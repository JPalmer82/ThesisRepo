// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TileView.h"
#include "THNWordTileView.generated.h"

/**
 * 
 */
UCLASS()
class UTHNWordTileView : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, Category="UI")
	TObjectPtr<UTileView> WordTileView;
};
