// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THNExperimentationPuzzle.generated.h"

class UBoxComponent;
class UWidgetComponent;
class UCameraComponent;
class UTHNPuzzleInfoComponent;
class UTHNCameraManagerSubsystem;
class UTHNInteractionBoxComponent;

USTRUCT(BlueprintType)
struct FTHNExperimentationWave
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Amplitude = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Frequency = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Phase = 0;
};

UCLASS()
class ATHNExperimentationPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHNExperimentationPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWidgetComponent> WidgetComponent;
	
	UTextureRenderTarget2D* GetWidgetRenderTarget();
	
	UPROPERTY(EditAnywhere, Category="Debug")
	FTHNExperimentationWave WaveBL;
	
	UPROPERTY(EditAnywhere, Category="Debug")
	FTHNExperimentationWave WaveBR;
	
	UPROPERTY(EditAnywhere, Category="Debug")
	FTHNExperimentationWave TargetWaveBL = FTHNExperimentationWave(.481618, -3.597067, -8.766235);
	
	UPROPERTY(EditAnywhere, Category="Debug")
	FTHNExperimentationWave TargetWaveBR = FTHNExperimentationWave(.777618, 2.438537, 7.079522);
	
	void AdjustPhaseAmp(float PhaseDelta, float AmplitudeDelta);
	void AdjustFrequency(float FrequencyDelta);
	void SetBLWaveActive(bool Active);
	void SetBRWaveActive(bool Active);
	
	UPROPERTY(EditAnywhere, Category="Settings")
	float AdjustmentSensitivity = .5f;
	
private:
	UPROPERTY()
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> PuzzleMesh;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UTHNInteractionBoxComponent> InteractionBox;
	
	// UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	// TObjectPtr<UBoxComponent> WaveSwitcherCollider;
	//
	// UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	// TObjectPtr<UBoxComponent> AmplitudeCollider;
	//
	// UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	// TObjectPtr<UBoxComponent> FrequencyCollider;
	//
	// UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	// TObjectPtr<UBoxComponent> PhaseCollider;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> WaveBLInteractionBox;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> WaveBRInteractionBox;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UTHNPuzzleInfoComponent> PuzzleInfoComponent;
	
	TObjectPtr<UTHNCameraManagerSubsystem> CameraManagerSubsystem;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true), Category="Defaults")
	TObjectPtr<UMaterial> PuzzleScreenBaseMaterial;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstanceDynamic> PuzzleScreenMaterialInstance;
	
	FTimerHandle WaitForRenderTargetReadyHandle;
	
	bool BLWaveActive = false;
	bool BRWaveActive = false;
	bool IsPuzzleComplete = false;
	
	UFUNCTION()
	void OnInteract(AActor* InitiatorActor);
	
	UFUNCTION()
	void OnInteractEnd(AActor* InitiatorActor);
	
	UFUNCTION()
	void InitializePuzzleWidget();
	
	bool CheckSolution();
};
