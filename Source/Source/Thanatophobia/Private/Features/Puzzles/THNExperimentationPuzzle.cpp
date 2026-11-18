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
#include "Source/Thanatophobia/Thanatophobia.h"
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
	
	WaveBLInteractionBox = CreateDefaultSubobject<UBoxComponent>("WaveBLInteractionBox");
	WaveBRInteractionBox = CreateDefaultSubobject<UBoxComponent>("WaveBRInteractionBox");
	WaveBLInteractionBox->SetupAttachment(RootComponent);
	WaveBRInteractionBox->SetupAttachment(RootComponent);
	WaveBLInteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	WaveBRInteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	WaveBLInteractionBox->SetCollisionResponseToChannel(ECC_Interactable, ECR_Block);
	WaveBRInteractionBox->SetCollisionResponseToChannel(ECC_Interactable, ECR_Block);
	
	//Adjustment buttons
	// WaveSwitcherCollider = CreateDefaultSubobject<UBoxComponent>("WaveSwitcherCollider");
	// AmplitudeCollider = CreateDefaultSubobject<UBoxComponent>("AmplitudeCollider");
	// FrequencyCollider = CreateDefaultSubobject<UBoxComponent>("FrequencyCollider");
	// PhaseCollider = CreateDefaultSubobject<UBoxComponent>("PhaseCollider");
	//
	// WaveSwitcherCollider->SetupAttachment(RootComponent);
	// AmplitudeCollider->SetupAttachment(RootComponent);
	// FrequencyCollider->SetupAttachment(RootComponent);
	// PhaseCollider->SetupAttachment(RootComponent);
	//
	// WaveSwitcherCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	// AmplitudeCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	// FrequencyCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	// PhaseCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	//
	// WaveSwitcherCollider->SetCollisionResponseToChannel(ECC_Interactable, ECR_Ignore);
	// AmplitudeCollider->SetCollisionResponseToChannel(ECC_Interactable, ECR_Ignore);
	// FrequencyCollider->SetCollisionResponseToChannel(ECC_Interactable, ECR_Ignore);
	// PhaseCollider->SetCollisionResponseToChannel(ECC_Interactable, ECR_Ignore);
	
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
	WaveBL.Frequency = FMath::Clamp(WaveBL.Frequency, -5.f, 5.0);
	WaveBR.Frequency = FMath::Clamp(WaveBR.Frequency, -5.f, 5.0);
	
	if (!IsPuzzleComplete)
	{
		CheckSolution();
		PuzzleWidget->UpdateWidget(WaveBL, WaveBR);
	}
}

UTextureRenderTarget2D* ATHNExperimentationPuzzle::GetWidgetRenderTarget()
{
	return WidgetComponent->GetRenderTarget();
}

void ATHNExperimentationPuzzle::AdjustPhaseAmp(float PhaseDelta, float AmplitudeDelta)
{
	if (BLWaveActive)
	{
		WaveBL.Phase += PhaseDelta * AdjustmentSensitivity;
		WaveBL.Amplitude += AmplitudeDelta * AdjustmentSensitivity;
	}
	else if (BRWaveActive)
	{
		WaveBR.Phase += PhaseDelta * AdjustmentSensitivity;
		WaveBR.Amplitude += AmplitudeDelta * AdjustmentSensitivity;
	}
}

void ATHNExperimentationPuzzle::AdjustFrequency(float FrequencyDelta)
{
	if (BLWaveActive)
	{
		WaveBL.Frequency += FrequencyDelta * AdjustmentSensitivity;
	}
	else if (BRWaveActive)
	{
		WaveBR.Frequency += FrequencyDelta * AdjustmentSensitivity;
	}
}

void ATHNExperimentationPuzzle::SetBLWaveActive(bool Active)
{
	BLWaveActive = Active;
}

void ATHNExperimentationPuzzle::SetBRWaveActive(bool Active)
{
	BRWaveActive = Active;
}

void ATHNExperimentationPuzzle::OnInteract(AActor* InitiatorActor)
{
	if (UTHNGameManagerSubsystem* GameManager = GetGameInstance()->GetSubsystem<UTHNGameManagerSubsystem>())
	{
		GameManager->TrySwitchGameState(EGameState::Puzzle);
		ATHNPlayerController* PlayerController = Cast<ATHNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		CameraManagerSubsystem->LookAtTargetWithRadius(PlayerController, this, 45, GetComponentByClass<UTHNPuzzleInfoComponent>()->PuzzleInfo);
		SetActorTickEnabled(true);
		InteractionBox->DisableInteraction();
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
		InteractionBox->EnableInteraction();
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

bool ATHNExperimentationPuzzle::CheckSolution()
{
	float totalDifference = 0.f;
	
	for (int i = 0; i < 10; i++)
	{
		float x = (static_cast<float>(i) / 10) * TWO_PI;
		float targetSumVal =
			TargetWaveBL.Amplitude * sin(TargetWaveBL.Frequency * x + TargetWaveBL.Phase) +
				TargetWaveBR.Amplitude * sin(TargetWaveBR.Frequency * x + TargetWaveBR.Phase);
		
		float actualSumVal = WaveBL.Amplitude * sin(WaveBL.Frequency * x + WaveBL.Phase) +
				WaveBR.Amplitude * sin(WaveBR.Frequency * x + WaveBR.Phase);
		
		if (actualSumVal - targetSumVal > .5)
			return false;
		
		totalDifference += FMath::Abs(actualSumVal - targetSumVal);
	}
	
	//Check that frequencies are in correct direction
	if (WaveBL.Frequency * TargetWaveBL.Frequency < 0.f || WaveBR.Frequency * TargetWaveBR.Frequency < 0.f || totalDifference > .8)
	{
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("PASSED - Difference: %f"), totalDifference);
	GEngine->AddOnScreenDebugMessage(0, 8, FColor::Red, TEXT("PUZZLE COMPLETE"));
	IsPuzzleComplete = true;
	return true;
}

