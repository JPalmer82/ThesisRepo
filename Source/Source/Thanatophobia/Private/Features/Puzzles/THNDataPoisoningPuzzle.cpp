// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Puzzles/THNDataPoisoningPuzzle.h"

#include "Features/Characters/THNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Services/THNPlayerCameraService.h"
#include "Services/THNServiceLocator.h"

// Sets default values
ATHNDataPoisoningPuzzle::ATHNDataPoisoningPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATHNDataPoisoningPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCameraService = UTHNServiceLocator::GetService<UTHNPlayerCameraService>("PlayerCamera");
}

// Called every frame
void ATHNDataPoisoningPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHNDataPoisoningPuzzle::OnInteract(AActor* InitiatorActor)
{
	ATHNPlayerController* PlayerController = Cast<ATHNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerCameraService->LookAtTargetWithRadius(PlayerController, this, 45);
}

void ATHNDataPoisoningPuzzle::OnInteractEnd(AActor* InitiatorActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Finished looking at target"));
	ATHNPlayerController* PlayerController = Cast<ATHNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerCameraService->ReturnToDefaultCamera(PlayerController);
}

