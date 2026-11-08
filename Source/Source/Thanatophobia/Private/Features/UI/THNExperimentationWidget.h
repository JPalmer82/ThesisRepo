// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THNExperimentationWidget.generated.h"

struct FTHNExperimentationWave;
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
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterial> WaveSumBaseMaterial;
	
	virtual void InitializeWidget(UTextureRenderTarget2D* RT);
	
	void UpdateWidget(FTHNExperimentationWave WaveBL, FTHNExperimentationWave WaveBR);
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UImage> Graph_BL_Image;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UImage> Graph_BR_Image;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UImage> Graph_Sum_Image;
	
private:
	UPROPERTY()
	TObjectPtr<UTextureRenderTarget2D> WidgetRenderTarget;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> GraphBLInstance;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> GraphBRInstance;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> GraphSumInstance;
};
