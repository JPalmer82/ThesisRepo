// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Services/Interfaces/THNInteractableInterface.h"
#include "THNDataPoisoningPuzzle.generated.h"

class UTHNPlayerCameraService;

UCLASS()
class ATHNDataPoisoningPuzzle : public AActor, public ITHNInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHNDataPoisoningPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(AActor* InitiatorActor) override;
	virtual void OnInteractEnd(AActor* InitiatorActor) override;
	
private:
	class UTHNCameraManagerSubsystem* CameraSubsystem;
};
