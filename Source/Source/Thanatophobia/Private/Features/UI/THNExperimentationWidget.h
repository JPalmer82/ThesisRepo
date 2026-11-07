// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THNExperimentationWidget.generated.h"

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
	
	virtual void NativeConstruct() override;
private:
	UPROPERTY()
	TObjectPtr<UMaterialInstance> MaterialInstance;
	
	UPROPERTY()
	TObjectPtr<UTextureRenderTarget2D> WidgetRenderTarget;
};
