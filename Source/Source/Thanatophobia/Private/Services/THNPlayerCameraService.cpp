// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/THNPlayerCameraService.h"

#include "Camera/CameraComponent.h"
#include "Features/Characters/THNPlayerCharacter.h"
#include "Features/Characters/THNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Core/THNGameMode.h"

UTHNPlayerCameraService::UTHNPlayerCameraService()
{
	
}

void UTHNPlayerCameraService::InitializeService()
{
	//UE_LOG(LogTemp, Warning, TEXT("INITIALIZING CAMERA SERVICE"));
	OnPlayerInitialized.AddUniqueDynamic(this, &UTHNPlayerCameraService::RegisterPlayerCamera);
}

void UTHNPlayerCameraService::ShutdownService()
{
	//UE_LOG(LogTemp, Warning, TEXT("SHUTTING DOWN CAMERA SERVICE"));
}

void UTHNPlayerCameraService::UpdateCamera(FVector2D LookInput)
{
	//TODO: Cache base view when switching to puzzle
	//TODO: Clamp view distance if needed
	AActor* CurrentViewTarget = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget();
	UCameraComponent* CurrentCamera = Cast<UCameraComponent>(CurrentViewTarget->GetComponentByClass(UCameraComponent::StaticClass()));
	
	//FQuat Rot = FQuat::FindBetweenVectors(CurrentCamForward, CurrentCamForward + (Right * LookInput.X + Up + LookInput.Y) * .1);
	FRotator Rot = FRotator(-LookInput.Y, LookInput.X, 0);
	CurrentCamera->AddRelativeRotation(Rot);
	
	//UE_LOG(LogTemp, Warning, TEXT("Look Input: %s"), *(CurrentCamForward + (Right * LookInput.Y + Up + LookInput.X) * .1).ToString());
}

void UTHNPlayerCameraService::LookAtTargetWithRadius(ATHNPlayerController* PlayerController, AActor* TargetActor,
                                                     float Radius)
{
	PlayerController->SetViewTargetWithBlend(TargetActor, 1, VTBlend_Cubic);
}

void UTHNPlayerCameraService::ReturnToDefaultCamera(ATHNPlayerController* PlayerController)
{
	PlayerController->SetViewTargetWithBlend(Cast<ATHNPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)), 1, VTBlend_Cubic);
}

void UTHNPlayerCameraService::RegisterPlayerCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("Registering Player Camera"))
}
