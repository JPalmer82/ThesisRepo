// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/THNPlayerCameraService.h"

#include "Camera/CameraComponent.h"
#include "Features/Characters/THNPlayerCharacter.h"
#include "Features/Characters/THNPlayerController.h"
#include "GameFramework/GameState.h"
#include "Kismet/GameplayStatics.h"

UTHNPlayerCameraService::UTHNPlayerCameraService()
{
}

void UTHNPlayerCameraService::InitializeService()
{
	//UE_LOG(LogTemp, Warning, TEXT("INITIALIZING CAMERA SERVICE"));
}

void UTHNPlayerCameraService::ShutdownService()
{
	//UE_LOG(LogTemp, Warning, TEXT("SHUTTING DOWN CAMERA SERVICE"));
}

void UTHNPlayerCameraService::UpdateCamera(FVector2D LookInput)
{
	//TODO: Cache base view when switching to puzzle
	//TODO: Clamp view distance if needed
	//TODO: Fix rolling when looking at puzzle
	AActor* CurrentViewTarget = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget();
	UCameraComponent* CurrentCamera = Cast<UCameraComponent>(CurrentViewTarget->GetComponentByClass(UCameraComponent::StaticClass()));
	FVector CurrentCamForward = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget()->GetActorForwardVector();
	FVector Forward = CurrentCamForward;//CurrentCamera->GetForwardVector();
	FVector Right = FVector::CrossProduct(Forward, FVector(0, 0, 1));
	Right.Normalize();
	FVector Up = FVector::CrossProduct(Forward, Right);
	Up.Normalize();
	
	//FQuat Rot = FQuat::FindBetweenVectors(CurrentCamForward, CurrentCamForward + (Right * LookInput.X + Up + LookInput.Y) * .1);
	FRotator Rot = FRotator(-LookInput.Y, LookInput.X, 0);
	
	CurrentCamera->AddLocalRotation(Rot);
	
	UE_LOG(LogTemp, Warning, TEXT("Look Input: %s"), *(CurrentCamForward + (Right * LookInput.Y + Up + LookInput.X) * .1).ToString());
}

void UTHNPlayerCameraService::LerpToNewLocation(float TimeToTake, ATHNPlayerController* PlayerController)
{
	// FTimerHandle LerpTimer;
	// FTimerDelegate LerpDelegate;
	//
	// UE_LOG(LogTemp, Warning, TEXT("%f"), TimeToTake);
	//
	// if (TimeToTake <= 0.0)
	// {
	// 	return;
	// }
	//
	// LerpDelegate.BindUObject(this, &UTHNPlayerCameraService::LerpToNewLocation, TimeToTake - GetWorld()->GetDeltaSeconds(), PlayerController);
	// PlayerController->GetWorldTimerManager().SetTimerForNextTick(LerpDelegate);
}

void UTHNPlayerCameraService::LookAtTargetWithRadius(ATHNPlayerController* PlayerController, AActor* TargetActor, float Radius)
{
	// UE_LOG(LogTemp, Warning, TEXT("Looking at target"));
	//
	// FTimerHandle LerpTimer;
	// FTimerDelegate LerpDelegate;
	// LerpDelegate.BindUObject(this, &UTHNPlayerCameraService::LerpToNewLocation, 5.f, PlayerController);
	// PlayerController->GetWorldTimerManager().SetTimerForNextTick(LerpDelegate);
	
	PlayerController->SetViewTargetWithBlend(TargetActor, 1, VTBlend_Cubic);
}

void UTHNPlayerCameraService::ReturnToDefaultCamera(ATHNPlayerController* PlayerController)
{
	PlayerController->SetViewTargetWithBlend(Cast<ATHNPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)), 1, VTBlend_Cubic);
}
