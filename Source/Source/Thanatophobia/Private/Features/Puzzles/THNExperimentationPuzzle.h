// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THNExperimentationPuzzle.generated.h"

class UCameraComponent;
class UTHNPuzzleInfoComponent;
class UTHNCameraManagerSubsystem;
class UTHNInteractionBoxComponent;

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Graph1Phase = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Graph2Phase = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Graph1Frequency = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Graph2Frequency = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Graph1Amplitude = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Graph2Amplitude = 1;
	
	UFUNCTION(BlueprintCallable)
	void IncrementGraph1Frequency(float value) { Graph1Frequency += value; }
	
	UFUNCTION(BlueprintCallable)
	void IncrementGraph2Frequency(float value) { Graph2Frequency += value; }
	
	UFUNCTION(BlueprintCallable)
	void IncrementGraph1Amplitude(float value) { Graph1Amplitude += value; }
	
	UFUNCTION(BlueprintCallable)
	void IncrementGraph2Amplitude(float value) { Graph2Amplitude += value; }
	
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
	
	UFUNCTION()
	void OnInteract(AActor* InitiatorActor);
	
	UFUNCTION()
	void OnInteractEnd(AActor* InitiatorActor);
};
