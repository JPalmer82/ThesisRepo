// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THNPowerDistributor.generated.h"

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
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UTHNInteractionBoxComponent> InteractionBoxComponent;
};
