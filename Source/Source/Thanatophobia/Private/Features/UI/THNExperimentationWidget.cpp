// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THNExperimentationWidget.h"

#include "Components/Image.h"

void UTHNExperimentationWidget::InitializeWidget(UTextureRenderTarget2D* RT)
{
	if (RT == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("THN: Experimentation Puzzle Render Target is null!"));
	}
	
	WidgetRenderTarget = RT;
	GraphBLInstance = UMaterialInstanceDynamic::Create(WaveBaseMaterial, this);
	Graph_BL_Image->SetBrushFromMaterial(GraphBLInstance);
	
	GraphBRInstance = UMaterialInstanceDynamic::Create(WaveBaseMaterial, this);
	Graph_BR_Image->SetBrushFromMaterial(GraphBRInstance);
}
