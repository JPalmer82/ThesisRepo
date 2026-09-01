// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/THNServiceInterface.h"
#include "UObject/Object.h"
#include "THNPlayerCameraService.generated.h"

class ATHNPlayerController;
class ATHNPlayerCharacter;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTHNRegisterPlayerCameraDelegate);

UCLASS()
class UTHNPlayerCameraService : public UObject, public ITHNServiceInterface
{
	GENERATED_BODY()
	
public:
	UTHNPlayerCameraService();
	
	virtual void InitializeService() override;
	virtual void ShutdownService() override;
	
	void UpdateCamera(FVector2D LookInput);
	
	//TODO: Make PlayerController a member variable after creating a bootstrapper scene
	void LookAtTargetWithRadius(ATHNPlayerController* PlayerController, AActor* TargetActor, float Radius);
	
	void ReturnToDefaultCamera(ATHNPlayerController* PlayerController);
	
	UFUNCTION()
	void RegisterPlayerCamera();
	
	FTHNRegisterPlayerCameraDelegate OnPlayerInitialized;
};
