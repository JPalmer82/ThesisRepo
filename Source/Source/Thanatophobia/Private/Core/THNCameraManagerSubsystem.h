// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "THNCameraManagerSubsystem.generated.h"

class UCameraComponent;
struct FPuzzleInfo;
/**
 * 
 */
DECLARE_DELEGATE_OneParam(FTHNRegisterPlayerCameraDelegate, UCameraComponent* /*CurrentPlayerCamera*/);

class ATHNPlayerController;

enum class ECameraStates
{
	DefaultGame,
	PuzzleInteraction,
	Cutscene
};

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
	void RegisterPlayerCamera(UCameraComponent* PlayerCamera);
	
	FTHNRegisterPlayerCameraDelegate OnPlayerInitialized;
	
private:
	float GetAngleBetweenVectors(FVector vec1, FVector vec2);
	
	void UpdateDefaultGameCamera(FVector2D LookInput);
	void UpdatePuzzleInteractionCamera(FVector2D LookInput);
	
	FVector CachedViewTargetForward = FVector(0);
	
	UPROPERTY()
	AActor* CachedViewTarget = nullptr;
	
	UPROPERTY()
	UCameraComponent* PlayerCamera;
	
	FVector2D AccumulatedLookInput = FVector2D(0.0f, 0.0f);
	FVector2D CachedAccumulatedLookInput = FVector2D(0.0f, 0.0f);
	
	ECameraStates CurrentCameraState = ECameraStates::DefaultGame;
};
