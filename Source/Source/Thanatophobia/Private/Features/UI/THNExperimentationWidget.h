// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THNExperimentationWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class UTHNExperimentationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterial> WaveBaseMaterial;
	
	virtual void InitializeWidget(UTextureRenderTarget2D* RT);
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UImage> Graph_BL_Image;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UImage> Graph_BR_Image;
	
private:
	UPROPERTY()
	TObjectPtr<UTextureRenderTarget2D> WidgetRenderTarget;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> GraphBLInstance;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> GraphBRInstance;
};
