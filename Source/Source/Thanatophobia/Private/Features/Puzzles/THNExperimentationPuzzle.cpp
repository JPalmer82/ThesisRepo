// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Puzzles/THNExperimentationPuzzle.h"

#include "THNPuzzleInfoComponent.h"
#include "Components/WidgetComponent.h"
#include "Core/THNCameraManagerSubsystem.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Features/Characters/THNPlayerController.h"
#include "Features/UI/THNExperimentationWidget.h"
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
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATHNExperimentationPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	GetGameInstance()->GetSubsystem<UTHNGameManagerSubsystem>()->RegisterExperimentationPuzzle(this);
	CameraManagerSubsystem = GetGameInstance()->GetSubsystem<UTHNCameraManagerSubsystem>();
	
	//The widget component's render target isn't immediately initialized, so we have to delay initializationw
	GetWorldTimerManager().SetTimer(WaitForRenderTargetReadyHandle, this, &ATHNExperimentationPuzzle::InitializePuzzleWidget, 1);
	
	PuzzleScreenMaterialInstance = UMaterialInstanceDynamic::Create(PuzzleScreenBaseMaterial, this);
	PuzzleMesh->SetMaterial(1, PuzzleScreenMaterialInstance);

	SetActorTickEnabled(false);
}

// Called every frame
void ATHNExperimentationPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UTHNExperimentationWidget* PuzzleWidget = Cast<UTHNExperimentationWidget>(WidgetComponent->GetWidget());
	
	//Clamps maximum amplitude of the sum of waves to ~2.71828
	WaveBL.Amplitude = FMath::Clamp(WaveBL.Amplitude, -1.35914, 1.35914);
	WaveBR.Amplitude = FMath::Clamp(WaveBR.Amplitude, -1.35914, 1.35914);
	WaveBL.Frequency = FMath::Clamp(WaveBL.Frequency, -3.0, 3.0);
	WaveBR.Frequency = FMath::Clamp(WaveBR.Frequency, -3.0, 3.0);
	PuzzleWidget->UpdateWidget(WaveBL, WaveBR);
}

UTextureRenderTarget2D* ATHNExperimentationPuzzle::GetWidgetRenderTarget()
{
	return WidgetComponent->GetRenderTarget();
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

void ATHNExperimentationPuzzle::InitializePuzzleWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("InitializePuzzleWidget"));
	UTHNExperimentationWidget* PuzzleWidget = Cast<UTHNExperimentationWidget>(WidgetComponent->GetWidget());
	PuzzleWidget->InitializeWidget(WidgetComponent->GetRenderTarget());
	PuzzleScreenMaterialInstance->SetTextureParameterValue("PuzzleWidget", WidgetComponent->GetRenderTarget());
	GetWorldTimerManager().ClearTimer(WaitForRenderTargetReadyHandle);
}

