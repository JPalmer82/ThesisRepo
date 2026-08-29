// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Puzzles/THNNeuronPuzzleManager.h"
#include "THNNeuronActor.h"

// Sets default values
ATHNNeuronPuzzleManager::ATHNNeuronPuzzleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATHNNeuronPuzzleManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATHNNeuronPuzzleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

