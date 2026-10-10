// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Puzzles/THNPowerDistributor.h"

#include "Utility/THNInteractionBoxComponent.h"

// Sets default values
ATHNPowerDistributor::ATHNPowerDistributor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	
	InteractionBoxComponent = CreateDefaultSubobject<UTHNInteractionBoxComponent>(TEXT("InteractionBoxComponent"));
	InteractionBoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATHNPowerDistributor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATHNPowerDistributor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

