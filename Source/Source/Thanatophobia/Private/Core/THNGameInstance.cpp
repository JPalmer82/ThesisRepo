// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/THNGameInstance.h"

#include "Services/THNPlayerCameraService.h"
#include "Services/THNServiceLocator.h"

void UTHNGameInstance::Init()
{
	Super::Init();
	
	UTHNPlayerCameraService* PlayerCameraService = NewObject<UTHNPlayerCameraService>(this, UTHNPlayerCameraService::StaticClass());
	if (PlayerCameraService)
	{
		PlayerCameraService->InitializeService();
		UTHNServiceLocator::RegisterService("PlayerCamera", PlayerCameraService);
	}
}

void UTHNGameInstance::Shutdown()
{
	//shut down all services
	//TODO: loop through and shut down all services in the service locator class
	if (UTHNPlayerCameraService* PlayerCameraService = UTHNServiceLocator::GetService<UTHNPlayerCameraService>("PlayerCamera"))
	{
		PlayerCameraService->ShutdownService();
	}
	
	UTHNServiceLocator::ClearServices();
	
	Super::Shutdown();
}
