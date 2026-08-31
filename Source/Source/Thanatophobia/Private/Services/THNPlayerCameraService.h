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
UCLASS()
class UTHNPlayerCameraService : public UObject, public ITHNServiceInterface
{
	GENERATED_BODY()
	
public:
	UTHNPlayerCameraService();
	
	virtual void InitializeService() override;
	virtual void ShutdownService() override;
	
	void UpdateCamera(FVector2D LookInput);
	
	void LerpToNewLocation(float TimeToTake, ATHNPlayerController* PlayerController);
	
	//TODO: Make PlayerController a member variable after creating a bootstrapper scene
	void LookAtTargetWithRadius(ATHNPlayerController* PlayerController, AActor* TargetActor, float Radius);
	
	void ReturnToDefaultCamera(ATHNPlayerController* PlayerController);
};
