// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Puzzles/THNDataPoisoningPuzzle.h"

#include "THNPuzzleInfoComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/WidgetComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Core/THNCameraManagerSubsystem.h"
#include "Features/Characters/THNPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATHNDataPoisoningPuzzle::ATHNDataPoisoningPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SceneComponent);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneComponent);
	InteractionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionCollider"));
	InteractionCollider->SetupAttachment(StaticMesh);
	
	UISceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("UISceneCapture"));
	UISceneCapture->SetupAttachment(SceneComponent);
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(UISceneCapture);
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionComponent"));
	WidgetInteractionComponent->SetupAttachment(Widget);
}

// Called when the game starts or when spawned
void ATHNDataPoisoningPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	CameraSubsystem = GetGameInstance()->GetSubsystem<UTHNCameraManagerSubsystem>();
	SetActorTickEnabled(false);
}

// Called every frame
void ATHNDataPoisoningPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	if (UCameraComponent* CurrentCam = CameraSubsystem->GetCurrentCamera())
	{
		FHitResult OutHit;
		GetWorld()->LineTraceSingleByChannel(OutHit, CurrentCam->GetComponentLocation(), CurrentCam->GetComponentLocation() + CurrentCam->GetForwardVector() * 1000, ECC_Visibility);
		DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 5, 32, FColor::Red);
	}
}

void ATHNDataPoisoningPuzzle::OnInteract(AActor* InitiatorActor)
{
	ATHNPlayerController* PlayerController = Cast<ATHNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CameraSubsystem->LookAtTargetWithRadius(PlayerController, this, 45, GetComponentByClass<UTHNPuzzleInfoComponent>()->PuzzleInfo);
	SetActorTickEnabled(true);
}

void ATHNDataPoisoningPuzzle::OnInteractEnd(AActor* InitiatorActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Finished looking at target"));
	ATHNPlayerController* PlayerController = Cast<ATHNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CameraSubsystem->ReturnToDefaultCamera(PlayerController);
	SetActorTickEnabled(false);
}

