// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Puzzles/THNPuzzleInfoComponent.h"

// Sets default values for this component's properties
UTHNPuzzleInfoComponent::UTHNPuzzleInfoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTHNPuzzleInfoComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PuzzleInfo.Camera = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));
	if (PuzzleInfo.Camera == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find puzzle camera"));
		return;
	}

	PuzzleInfo.InitialCameraRotation = PuzzleInfo.Camera->GetRelativeRotation().Quaternion();
}


