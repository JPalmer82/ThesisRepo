// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Props/THNIncubator.h"

#include "Components/BoxComponent.h"
#include "Features/Characters/THNPlayerCharacter.h"
#include "Services/THNGameManagerSubsystem.h"
#include "Utility/THNInteractionBoxComponent.h"

// Sets default values
ATHNIncubator::ATHNIncubator()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	InteractionBox = CreateDefaultSubobject<UTHNInteractionBoxComponent>(FName("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->OnBoxInteract.AddUniqueDynamic(this, &ATHNIncubator::OnInteract);
	InteractionBox->OnBoxInteractEnd.AddUniqueDynamic(this, &ATHNIncubator::OnInteractEnd);
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
	if (UTHNGameManagerSubsystem* GameManager = GetGameInstance()->GetSubsystem<UTHNGameManagerSubsystem>())
	{
		GameManager->TrySwitchGameState(EGameState::Puzzle);
		ChangeToIncubatorCamera(InitiatorActor);
		if (Cast<ATHNPlayerCharacter>(InitiatorActor))
		{
			Cast<ATHNPlayerCharacter>(InitiatorActor)->SwitchToMappingContext(IncubatorMappingContext);
		}
	}
}

void ATHNIncubator::OnInteractEnd(AActor* InitiatorActor)
{
	if (UTHNGameManagerSubsystem* GameManager = GetGameInstance()->GetSubsystem<UTHNGameManagerSubsystem>())
	{
		GameManager->TrySwitchGameState(EGameState::Default);
		ChangeToPlayerCamera(InitiatorActor);
		if (Cast<ATHNPlayerCharacter>(InitiatorActor))
		{
			Cast<ATHNPlayerCharacter>(InitiatorActor)->SwitchToMappingContext(DefaultMappingContext);
		}
	}
}

