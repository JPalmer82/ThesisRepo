// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Puzzles/THNExperimentationPuzzle.h"

#include "THNPuzzleInfoComponent.h"
#include "Core/THNCameraManagerSubsystem.h"
#include "Features/Characters/THNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Services/THNGameManagerSubsystem.h"
#include "Utility/THNInteractionBoxComponent.h"

class UTHNPuzzleInfoComponent;
// Sets default values
ATHNExperimentationPuzzle::ATHNExperimentationPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	
	PuzzleMesh = CreateDefaultSubobject<UStaticMeshComponent>("PuzzleMesh");
	PuzzleMesh->SetupAttachment(RootComponent);
	
	InteractionBox = CreateDefaultSubobject<UTHNInteractionBoxComponent>("InteractionBox");
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->OnBoxInteract.AddUniqueDynamic(this, &ATHNExperimentationPuzzle::OnInteract);
	InteractionBox->OnBoxInteractEnd.AddUniqueDynamic(this, &ATHNExperimentationPuzzle::OnInteractEnd);
	
	PuzzleInfoComponent = CreateDefaultSubobject<UTHNPuzzleInfoComponent>("PuzzleInfoComponent");
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(PuzzleMesh);
}

// Called when the game starts or when spawned
void ATHNExperimentationPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	GetGameInstance()->GetSubsystem<UTHNGameManagerSubsystem>()->RegisterExperimentationPuzzle(this);
	CameraManagerSubsystem = GetGameInstance()->GetSubsystem<UTHNCameraManagerSubsystem>();
	
	SetActorTickEnabled(false);
}

// Called every frame
void ATHNExperimentationPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATHNExperimentationPuzzle::OnInteract(AActor* InitiatorActor)
{
	if (UTHNGameManagerSubsystem* GameManager = GetGameInstance()->GetSubsystem<UTHNGameManagerSubsystem>())
	{
		GameManager->TrySwitchGameState(EGameState::Puzzle);
		ATHNPlayerController* PlayerController = Cast<ATHNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		CameraManagerSubsystem->LookAtTargetWithRadius(PlayerController, this, 45, GetComponentByClass<UTHNPuzzleInfoComponent>()->PuzzleInfo);
		SetActorTickEnabled(true);
		//UISceneCapture->SetVisibility(true);
	}
}

void ATHNExperimentationPuzzle::OnInteractEnd(AActor* InitiatorActor)
{
	if (UTHNGameManagerSubsystem* GameManager = GetGameInstance()->GetSubsystem<UTHNGameManagerSubsystem>())
	{
		GameManager->TrySwitchGameState(EGameState::Default);
		UE_LOG(LogTemp, Warning, TEXT("Finished looking at target"));
		ATHNPlayerController* PlayerController = Cast<ATHNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		CameraManagerSubsystem->ReturnToDefaultCamera(PlayerController);
		SetActorTickEnabled(false);
		//UISceneCapture->SetVisibility(false);
	}
}

