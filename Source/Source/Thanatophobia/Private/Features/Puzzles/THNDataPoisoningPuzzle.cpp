// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Puzzles/THNDataPoisoningPuzzle.h"

#include "THNPuzzleInfoComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/WidgetComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Core/THNCameraManagerSubsystem.h"
#include "Core/THNPuzzleManagerSubsystem.h"
#include "Features/Characters/THNPlayerController.h"
#include "Features/UI/THNDataPoisoningWidget.h"
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
	
	OnClickDelegate.AddUniqueDynamic(this, &ATHNDataPoisoningPuzzle::OnClick);
	
}

// Called when the game starts or when spawned
void ATHNDataPoisoningPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	CameraSubsystem = GetGameInstance()->GetSubsystem<UTHNCameraManagerSubsystem>();
	SetActorTickEnabled(false);
	
	ATHNPlayerController* PlayerController = Cast<ATHNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->EnableInput(PlayerController);
	PlayerController->bEnableClickEvents = true;
	
	DataPoisoningWidget = Cast<UTHNDataPoisoningWidget>(Widget->GetWidget());
	
	UTHNPuzzleManagerSubsystem* PuzzleManagerSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UTHNPuzzleManagerSubsystem>();
	PuzzleManagerSubsystem->RegisterDataPoisoningPuzzle(this);
	
	TArray<FName> Rows = SentimentTable->GetRowNames();
	int RandOffset = FMath::RandRange(0, Rows.Num() - 1);
	
	for (int i = 0; i < Settings.NumWordsPerPages * Settings.NumPages; i++)
	{
		FSentimentTable* Table = SentimentTable->FindRow<FSentimentTable>(Rows[(i + RandOffset) % Rows.Num() - 1], "");
		Words.Add(FDataPoisoningWord(Table->Word, Table->Sentiment));
	}
}

// Called every frame
void ATHNDataPoisoningPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (UCameraComponent* CurrentCam = CameraSubsystem->GetCurrentCamera())
	{
		FHitResult OutHit;
		FCollisionQueryParams CollisionParams;
		CollisionParams.bTraceComplex = true;
		CollisionParams.bReturnFaceIndex = true;
		
		//TODO: Add custom trace channel
		GetWorld()->LineTraceSingleByChannel(
			OutHit, 
			CurrentCam->GetComponentLocation(), 
			CurrentCam->GetComponentLocation() + CurrentCam->GetForwardVector() * 1000, 
			ECC_Visibility,
			CollisionParams);
		
		FVector2D HitUV;
		UGameplayStatics::FindCollisionUV(OutHit, 0, HitUV);
		
		FVector NewInteractLocation = FVector(
			WidgetInteractionComponent->GetRelativeLocation().X,
			FMath::Lerp(Settings.RelativeScreenSize.X, -Settings.RelativeScreenSize.X, 1 - HitUV.X),
			FMath::Lerp(Settings.RelativeScreenSize.Y, -Settings.RelativeScreenSize.Y, 1 - HitUV.Y));
		WidgetInteractionComponent->SetRelativeLocation(NewInteractLocation);
	}
}

void ATHNDataPoisoningPuzzle::OnInteract(AActor* InitiatorActor)
{
	ATHNPlayerController* PlayerController = Cast<ATHNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CameraSubsystem->LookAtTargetWithRadius(PlayerController, this, 45, GetComponentByClass<UTHNPuzzleInfoComponent>()->PuzzleInfo);
	SetActorTickEnabled(true);
	UISceneCapture->SetVisibility(true);
}

void ATHNDataPoisoningPuzzle::OnInteractEnd(AActor* InitiatorActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Finished looking at target"));
	ATHNPlayerController* PlayerController = Cast<ATHNPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CameraSubsystem->ReturnToDefaultCamera(PlayerController);
	SetActorTickEnabled(false);
	UISceneCapture->SetVisibility(false);
}

void ATHNDataPoisoningPuzzle::OnClick(AActor* InteractActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("Current actor: %s"), *InteractActor->GetName());
	WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
	WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
}

