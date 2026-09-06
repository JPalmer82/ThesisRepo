// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "THNCameraManagerSubsystem.generated.h"

struct FPuzzleInfo;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTHNRegisterPlayerCameraDelegate);

class ATHNPlayerController;

UCLASS()
class UTHNCameraManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	void UpdateCamera(FVector2D LookInput);
	
	//TODO: Make PlayerController a member variable after creating a bootstrapper scene
	void LookAtTargetWithRadius(ATHNPlayerController* PlayerController, AActor* TargetActor, float Radius, FPuzzleInfo PuzzleInfo);
	
	void ReturnToDefaultCamera(ATHNPlayerController* PlayerController);
	
	UFUNCTION()
	void RegisterPlayerCamera();
	
	FTHNRegisterPlayerCameraDelegate OnPlayerInitialized;
	
private:
	float GetAngleBetweenVectors(FVector vec1, FVector vec2);
	
	FVector CachedViewTargetForward = FVector(0);
	
	UPROPERTY()
	AActor* CachedViewTarget = nullptr;
	
	FVector2D AccumulatedLookIinput = FVector2D(0.0f, 0.0f);
	FVector2D CachedAccumulatedLookInput = FVector2D(0.0f, 0.0f);
};
