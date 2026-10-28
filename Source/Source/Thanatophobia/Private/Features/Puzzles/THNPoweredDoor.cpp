// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Puzzles/THNPoweredDoor.h"

#include "Services/THNPowerManagerSubsystem.h"

// Sets default values
ATHNPoweredDoor::ATHNPoweredDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATHNPoweredDoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (ShouldStartOpen)
		OpenDoor();
	
	if (UTHNPowerManagerSubsystem* PowerManager = GetGameInstance()->GetSubsystem<UTHNPowerManagerSubsystem>())
	{
		switch(ConnectedRoom)
		{
			case EPoweredRooms::Office:
				PowerManager->OnOfficePowerActivated.AddUniqueDynamic(this, &ATHNPoweredDoor::OpenDoor);
				PowerManager->OnOfficePowerDeactivated.AddUniqueDynamic(this, &ATHNPoweredDoor::CloseDoor);
				break;
			case EPoweredRooms::Experimentation:
				PowerManager->OnExperimentationPowerActivated.AddUniqueDynamic(this, &ATHNPoweredDoor::OpenDoor);
				PowerManager->OnExperimentationPowerDeactivated.AddUniqueDynamic(this, &ATHNPoweredDoor::CloseDoor);
				break;
			case EPoweredRooms::ResearchAndDevelopment:
				PowerManager->OnRnDPowerActivated.AddUniqueDynamic(this, &ATHNPoweredDoor::OpenDoor);
				PowerManager->OnRnDPowerDeactivated.AddUniqueDynamic(this, &ATHNPoweredDoor::CloseDoor);
				break;
			case EPoweredRooms::Security:
				PowerManager->OnSecurityPowerActivated.AddUniqueDynamic(this, &ATHNPoweredDoor::OpenDoor);
				PowerManager->OnSecurityPowerDeactivated.AddUniqueDynamic(this, &ATHNPoweredDoor::CloseDoor);
			default:
				UE_LOG(LogTemp, Error, TEXT("Unsupported power room type"));
		}
	}
}

void ATHNPoweredDoor::OpenDoor()
{
	Mesh->SetVisibility(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATHNPoweredDoor::CloseDoor()
{
	Mesh->SetVisibility(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

