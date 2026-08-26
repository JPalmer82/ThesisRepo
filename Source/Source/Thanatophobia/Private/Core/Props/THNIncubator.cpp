// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Props/THNIncubator.h"

#include "Core/Characters/THNPlayerCharacter.h"

// Sets default values
ATHNIncubator::ATHNIncubator()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATHNIncubator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATHNIncubator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATHNIncubator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATHNIncubator::OnInteract(AActor* InitiatorActor)
{
	ChangeToIncubatorCamera(InitiatorActor);
	if (Cast<ATHNPlayerCharacter>(InitiatorActor))
	{
		Cast<ATHNPlayerCharacter>(InitiatorActor)->SwitchToMappingContext(IncubatorMappingContext);
	}
}

void ATHNIncubator::OnInteractEnd(AActor* InitiatorActor)
{
	ChangeToPlayerCamera(InitiatorActor);
	if (Cast<ATHNPlayerCharacter>(InitiatorActor))
	{
		Cast<ATHNPlayerCharacter>(InitiatorActor)->SwitchToMappingContext(DefaultMappingContext);
	}
}

