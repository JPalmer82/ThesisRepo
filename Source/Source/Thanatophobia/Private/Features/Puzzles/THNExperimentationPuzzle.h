// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THNExperimentationPuzzle.generated.h"

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
	
private:
	UPROPERTY()
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> PuzzleMesh;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UTHNInteractionBoxComponent> InteractionBox;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UTHNPuzzleInfoComponent> PuzzleInfoComponent;
	
	TObjectPtr<UTHNCameraManagerSubsystem> CameraManagerSubsystem;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true), Category="Defaults")
	TObjectPtr<UMaterial> PuzzleScreenBaseMaterial;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstanceDynamic> PuzzleScreenMaterialInstance;
	
	FTimerHandle WaitForRenderTargetReadyHandle;
	
	UFUNCTION()
	void OnInteract(AActor* InitiatorActor);
	
	UFUNCTION()
	void OnInteractEnd(AActor* InitiatorActor);
	
	UFUNCTION()
	void InitializePuzzleWidget();
};
