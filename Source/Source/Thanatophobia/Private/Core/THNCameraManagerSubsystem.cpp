// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/THNCameraManagerSubsystem.h"

#include "Camera/CameraComponent.h"
#include "Features/Characters/THNPlayerCharacter.h"
#include "Features/Characters/THNPlayerController.h"
#include "Features/Puzzles/THNPuzzleInfoComponent.h"
#include "Kismet/GameplayStatics.h"

void UTHNCameraManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	OnPlayerInitialized.BindUObject(this, &UTHNCameraManagerSubsystem::RegisterPlayerCamera);
}

void UTHNCameraManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UTHNCameraManagerSubsystem::UpdateCamera(FVector2D LookInput)
{
	switch (CurrentCameraState)
	{
		case ECameraStates::DefaultGame:
			UpdateDefaultGameCamera(LookInput);
		break;
		
		case ECameraStates::PuzzleInteraction:
			UpdatePuzzleInteractionCamera(LookInput);
		break;
		
		default:
			UE_LOG(LogTemp, Warning, TEXT("THN: Unhandled Camera State"))
	}
}

void UTHNCameraManagerSubsystem::LookAtTargetWithRadius(ATHNPlayerController* PlayerController, AActor* TargetActor,
	float Radius, FPuzzleInfo PuzzleInfo)
{
	PuzzleInfo.Camera->SetRelativeRotation(PuzzleInfo.InitialCameraRotation);
	PlayerController->SetViewTargetWithBlend(TargetActor, 1, VTBlend_Cubic);

	CachedViewTarget = TargetActor;
	AccumulatedLookIinput = FVector2D(0.0f, 0.0f);
	CurrentCameraState = ECameraStates::PuzzleInteraction;
}

void UTHNCameraManagerSubsystem::ReturnToDefaultCamera(ATHNPlayerController* PlayerController)
{
	PlayerController->SetViewTargetWithBlend(Cast<ATHNPlayerCharacter>(
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)), 1, VTBlend_Cubic);
	CurrentCameraState = ECameraStates::DefaultGame;
}

void UTHNCameraManagerSubsystem::RegisterPlayerCamera(UCameraComponent* CurrentPlayerCamera)
{
	UE_LOG(LogTemp, Warning, TEXT("Registering Player Camera"))
	PlayerCamera = CurrentPlayerCamera;
}

float UTHNCameraManagerSubsystem::GetAngleBetweenVectors(FVector vec1, FVector vec2)
{
	vec1.Normalize();
	vec2.Normalize();
	
	float dot = FVector::DotProduct(vec1, vec2);
	return (acos(dot) * 180) / PI;
}

void UTHNCameraManagerSubsystem::UpdateDefaultGameCamera(FVector2D LookInput)
{
	//TODO: Separate camera from control rotation
}

void UTHNCameraManagerSubsystem::UpdatePuzzleInteractionCamera(FVector2D LookInput)
{
	//Get camera attached to current puzzle
	AActor* CurrentViewTarget = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget();
	UCameraComponent* CurrentCamera = Cast<UCameraComponent>(CurrentViewTarget->GetComponentByClass(UCameraComponent::StaticClass()));
	
	//Cache the 2D Look vector
	CachedAccumulatedLookInput = AccumulatedLookIinput;
	AccumulatedLookIinput += FVector2D(LookInput.X, -LookInput.Y);
	
	//Convert to polar coordinates and back for easy clamping
	FVector2D OutPolar;
	FMath::CartesianToPolar(AccumulatedLookIinput, OutPolar);
	OutPolar.X = FMath::Clamp(OutPolar.X, -80, 80);
	FMath::PolarToCartesian(OutPolar, AccumulatedLookIinput);

	//Add rotation if clamped look input is different from cached look input
	FRotator Rot = FRotator(AccumulatedLookIinput.Y - CachedAccumulatedLookInput.Y, AccumulatedLookIinput.X - CachedAccumulatedLookInput.X, 0);
	CurrentCamera->AddRelativeRotation(Rot);
}
