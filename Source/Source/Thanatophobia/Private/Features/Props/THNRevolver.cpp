// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Props/THNRevolver.h"

// Sets default values
ATHNRevolver::ATHNRevolver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	RootComponent = SkeletalMeshComponent;
}

// Called when the game starts or when spawned
void ATHNRevolver::BeginPlay()
{
	Super::BeginPlay();
	
}

