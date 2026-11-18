// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "THNPuzzleInfoComponent.generated.h"

struct FPuzzleInfo
{
	FQuat InitialCameraRotation;
	UCameraComponent* Camera;
	UInputMappingContext* InputContext;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTHNPuzzleInfoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTHNPuzzleInfoComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	FPuzzleInfo PuzzleInfo;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> PuzzleInputMappingContext;
};
