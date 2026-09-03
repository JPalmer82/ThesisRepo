// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/THNGameMode.h"

#include "THNCameraManagerSubsystem.h"

void ATHNGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	UTHNCameraManagerSubsystem* CameraSubsystem = GetGameInstance()->GetSubsystem<UTHNCameraManagerSubsystem>();
	CameraSubsystem->OnPlayerInitialized.Broadcast();
}
