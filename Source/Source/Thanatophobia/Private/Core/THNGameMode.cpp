// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/THNGameMode.h"

#include "THNCameraManagerSubsystem.h"
#include "Camera/CameraComponent.h"
#include "Features/Characters/THNPlayerCharacter.h"

void ATHNGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	// if (ATHNPlayerCharacter* PlayerCharacter = Cast<ATHNPlayerCharacter>(NewPlayer->GetCharacter()))
	// {
	// 	UCameraComponent* CamComponent = Cast<UCameraComponent>(PlayerCharacter->GetComponentByClass(UCameraComponent::StaticClass()));
	// 	UTHNCameraManagerSubsystem* CameraSubsystem = GetGameInstance()->GetSubsystem<UTHNCameraManagerSubsystem>();
	// 	CameraSubsystem->OnPlayerInitialized.Execute(CamComponent);
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("THN: Failed to get player character"));
	// }
}
