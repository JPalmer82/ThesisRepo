// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/NPCs/THNDroneCharacter.h"

// Sets default values
ATHNDroneCharacter::ATHNDroneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATHNDroneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATHNDroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATHNDroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

