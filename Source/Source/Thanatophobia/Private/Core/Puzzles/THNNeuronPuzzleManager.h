// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THNNeuronPuzzleManager.generated.h"

UENUM(BlueprintType)
enum class EIncubatorPuzzleColor : uint8
{
	None UMETA(DisplayName = "None"),
	Red UMETA(DisplayName = "Red"),
	Green UMETA(DisplayName = "Green"),
	Blue UMETA(DisplayName = "Blue")
};

UCLASS()
class ATHNNeuronPuzzleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHNNeuronPuzzleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UseComponentPicker))
	TArray<UPrimitiveComponent*> NeuronSpawns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class ATHNNeuronActor*> Neurons;
};
