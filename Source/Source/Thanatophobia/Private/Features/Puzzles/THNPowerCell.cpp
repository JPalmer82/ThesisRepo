// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Puzzles/THNPowerCell.h"

#include "Services/THNPowerManagerSubsystem.h"
#include "Utility/THNInteractionBoxComponent.h"

// Sets default values
ATHNPowerCell::ATHNPowerCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	RootComponent = Root;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMesh->SetupAttachment(RootComponent);
	
	InteractionBox = CreateDefaultSubobject<UTHNInteractionBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(StaticMesh);
	InteractionBox->OnBoxInteract.AddUniqueDynamic(this, &ATHNPowerCell::OnInteract);
}

// Called when the game starts or when spawned
void ATHNPowerCell::BeginPlay()
{
	Super::BeginPlay();
	
	if (UTHNPowerManagerSubsystem* PowerManager = GetGameInstance()->GetSubsystem<UTHNPowerManagerSubsystem>())
	{
		PowerManagerSubsystem = PowerManager;
	}
}

void ATHNPowerCell::OnInteract(AActor* InitiatorActor)
{
	PowerManagerSubsystem->TryAddPowerCell();
	Destroy();
}
