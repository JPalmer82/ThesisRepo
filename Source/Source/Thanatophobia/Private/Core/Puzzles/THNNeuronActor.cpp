// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Puzzles/THNNeuronActor.h"

#include "Components/SphereComponent.h"

// Sets default values
ATHNNeuronActor::ATHNNeuronActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	SphereComponent->SetupAttachment(GetRootComponent());
	
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("SphereMesh"));
	SphereMesh->SetupAttachment(SphereComponent);

	RootComponent = SphereComponent;
}

// Called when the game starts or when spawned
void ATHNNeuronActor::BeginPlay()
{
	Super::BeginPlay();

	MaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);

	SphereMesh->SetMaterial(0, MaterialInstance);
}

// Called every frame
void ATHNNeuronActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

