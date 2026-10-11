// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THNPowerDistributor.generated.h"

class UTHNPowerManagerSubsystem;
class ATHNPowerCell;
class UTHNInteractionBoxComponent;
class UBoxComponent;

UCLASS()
class ATHNPowerDistributor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHNPowerDistributor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY()
	TObjectPtr<UTHNPowerManagerSubsystem> PowerManagerSubsystem;
	
	UPROPERTY()
	TArray<TObjectPtr<ATHNPowerCell>> HeldPowerCells;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TArray<TObjectPtr<UTHNInteractionBoxComponent>> InteractionBoxes;
	
	UFUNCTION()
	void OnOfficeInteract(AActor* InitiatorActor);
	
	UFUNCTION()
	void OnExperimentationInteract(AActor* InitiatorActor);
	
	UFUNCTION()
	void OnRnDInteract(AActor* InitiatorActor);
};
