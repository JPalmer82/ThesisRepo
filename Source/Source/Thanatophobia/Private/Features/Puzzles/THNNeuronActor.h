// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "THNNeuronPuzzleManager.h"
#include "GameFramework/Actor.h"
#include "THNNeuronActor.generated.h"

enum class EIncubatorPuzzleColor : uint8;
class USphereComponent;

UCLASS()
class ATHNNeuronActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHNNeuronActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Connections;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* BaseMaterial;

	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SphereMesh;

	UPROPERTY(BlueprintReadWrite)
	EIncubatorPuzzleColor CurrentColor = EIncubatorPuzzleColor::None;

	UPROPERTY(BlueprintReadWrite)
	int NeuronIndex;
};
