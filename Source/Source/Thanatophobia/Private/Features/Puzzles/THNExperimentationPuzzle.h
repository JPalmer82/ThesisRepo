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
