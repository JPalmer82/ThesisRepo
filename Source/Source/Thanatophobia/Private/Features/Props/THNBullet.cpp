// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Props/THNBullet.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/THNInteractionBoxComponent.h"

// Sets default values
ATHNBullet::ATHNBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	RootComponent = Root;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMesh->SetupAttachment(RootComponent);

	InteractionBox = CreateDefaultSubobject<UTHNInteractionBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(StaticMesh);
	InteractionBox->OnBoxInteract.AddUniqueDynamic(this, &ATHNBullet::OnInteract);
}

// Called when the game starts or when spawned
void ATHNBullet::BeginPlay()
{
	Super::BeginPlay();
}

void ATHNBullet::OnInteract(AActor* InitiatorActor)
{
	if (auto* Player = Cast<ATHNPlayerCharacter>(InitiatorActor))
	{
		Player->BulletCount++;
		Destroy();
	}
}

