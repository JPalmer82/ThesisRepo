// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Puzzles/THNPowerDistributor.h"

#include "Services/THNPowerManagerSubsystem.h"
#include "Utility/THNInteractionBoxComponent.h"

// Sets default values
ATHNPowerDistributor::ATHNPowerDistributor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	
	for (int i = 0; i < EPoweredRooms::RoomCount; i++)
	{
		TEnumAsByte<EPoweredRooms> RoomEnum = EPoweredRooms(i);
		FText EnumName = UEnum::GetDisplayValueAsText(RoomEnum);
		FString Name = FString(TEXT("{0}_InteractBox"));
		Name = FString::Format(*Name, {EnumName.ToString()});
		UTHNInteractionBoxComponent* NewInteractBox = CreateDefaultSubobject<UTHNInteractionBoxComponent>(FName(Name));
		NewInteractBox->SetupAttachment(RootComponent);
		InteractionBoxes.Add(NewInteractBox);
	}

	InteractionBoxes[EPoweredRooms::Office]->OnBoxInteract.AddUniqueDynamic(this, &ATHNPowerDistributor::OnOfficeInteract);
	InteractionBoxes[EPoweredRooms::Experimentation]->OnBoxInteract.AddUniqueDynamic(this, &ATHNPowerDistributor::OnExperimentationInteract);
	InteractionBoxes[EPoweredRooms::ResearchAndDevelopment]->OnBoxInteract.AddUniqueDynamic(this, &ATHNPowerDistributor::OnRnDInteract);
}

// Called when the game starts or when spawned
void ATHNPowerDistributor::BeginPlay()
{
	Super::BeginPlay();
	
	if (UTHNPowerManagerSubsystem* PowerManagerSubsystemReference = GetGameInstance()->GetSubsystem<UTHNPowerManagerSubsystem>())
	{
		PowerManagerSubsystem = PowerManagerSubsystemReference;
		PowerManagerSubsystem->RegisterPowerManager(this);
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("THN: Unable to register power distributor"))
	}
}

// Called every frame
void ATHNPowerDistributor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATHNPowerDistributor::OnOfficeInteract(AActor* InitiatorActor)
{
	PowerManagerSubsystem->HandlePowerSlotUpdated(this, EPoweredRooms::Office);
}

void ATHNPowerDistributor::OnExperimentationInteract(AActor* InitiatorActor)
{
	PowerManagerSubsystem->HandlePowerSlotUpdated(this, EPoweredRooms::Experimentation);
}

void ATHNPowerDistributor::OnRnDInteract(AActor* InitiatorActor)
{
	PowerManagerSubsystem->HandlePowerSlotUpdated(this, EPoweredRooms::ResearchAndDevelopment);
}

