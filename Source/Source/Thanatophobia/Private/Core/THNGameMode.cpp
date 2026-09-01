// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/THNGameMode.h"

#include "Services/THNPlayerCameraService.h"
#include "Services/THNServiceLocator.h"

void ATHNGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	UTHNPlayerCameraService* PlayerCameraService = UTHNServiceLocator::GetService<UTHNPlayerCameraService>("PlayerCamera");
	PlayerCameraService->OnPlayerInitialized.Broadcast();
}
