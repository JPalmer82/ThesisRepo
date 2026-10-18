// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THNPowerCell.generated.h"

class UTHNPowerManagerSubsystem;
class UTHNInteractionBoxComponent;

UCLASS()
class ATHNPowerCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHNPowerCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTHNInteractionBoxComponent> InteractionBox;
	
	UFUNCTION()
	void OnInteract(AActor* InitiatorActor);
	
	UPROPERTY()
	TObjectPtr<UTHNPowerManagerSubsystem> PowerManagerSubsystem;
};
