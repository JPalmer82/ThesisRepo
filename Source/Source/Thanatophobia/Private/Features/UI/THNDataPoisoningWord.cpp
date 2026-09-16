// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/UI/THNDataPoisoningWord.h"

void UTHNDataPoisoningWord::NativeConstruct()
{
	Super::NativeConstruct();
	
	WordButton->OnClicked.AddDynamic(this, &UTHNDataPoisoningWord::OnButtonClicked);
}

void UTHNDataPoisoningWord::OnButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Clicked"), *GetName());
}
