// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THNExperimentationWidget.h"

#include "Components/Image.h"
#include "Features/Puzzles/THNExperimentationPuzzle.h"

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
	
	GraphSumInstance = UMaterialInstanceDynamic::Create(WaveSumBaseMaterial, this);
	Graph_Sum_Image->SetBrushFromMaterial(GraphSumInstance);
}

void UTHNExperimentationWidget::UpdateWidget(FTHNExperimentationWave WaveBL, FTHNExperimentationWave WaveBR)
{
	GraphBLInstance->SetScalarParameterValue("Frequency", WaveBL.Frequency);
	GraphBLInstance->SetScalarParameterValue("Phase", WaveBL.Phase);
	GraphBLInstance->SetScalarParameterValue("Amplitude", WaveBL.Amplitude);
	
	GraphBRInstance->SetScalarParameterValue("Frequency", WaveBR.Frequency);
	GraphBRInstance->SetScalarParameterValue("Phase", WaveBR.Phase);
	GraphBRInstance->SetScalarParameterValue("Amplitude", WaveBR.Amplitude);
	
	GraphSumInstance->SetScalarParameterValue("Frequency1", WaveBL.Frequency);
	GraphSumInstance->SetScalarParameterValue("Phase1", WaveBL.Phase);
	GraphSumInstance->SetScalarParameterValue("Amplitude1", WaveBL.Amplitude);
	GraphSumInstance->SetScalarParameterValue("Frequency2", WaveBR.Frequency);
	GraphSumInstance->SetScalarParameterValue("Phase2", WaveBR.Phase);
	GraphSumInstance->SetScalarParameterValue("Amplitude2", WaveBR.Amplitude);
}