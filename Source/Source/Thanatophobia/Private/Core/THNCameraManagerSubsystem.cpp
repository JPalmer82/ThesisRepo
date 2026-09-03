// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/THNCameraManagerSubsystem.h"

#include "Camera/CameraComponent.h"
#include "Features/Characters/THNPlayerCharacter.h"
#include "Features/Characters/THNPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UTHNCameraManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	OnPlayerInitialized.AddUniqueDynamic(this, &UTHNCameraManagerSubsystem::RegisterPlayerCamera);
}

void UTHNCameraManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UTHNCameraManagerSubsystem::UpdateCamera(FVector2D LookInput)
{
	//TODO: Cache base view when switching to puzzle
	//TODO: Clamp view distance if needed
	AActor* CurrentViewTarget = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget();
	UCameraComponent* CurrentCamera = Cast<UCameraComponent>(CurrentViewTarget->GetComponentByClass(UCameraComponent::StaticClass()));
	
	FRotator Rot = FRotator(-LookInput.Y, LookInput.X, 0);
	CurrentCamera->AddRelativeRotation(Rot);
}

void UTHNCameraManagerSubsystem::LookAtTargetWithRadius(ATHNPlayerController* PlayerController, AActor* TargetActor,
	float Radius)
{
	PlayerController->SetViewTargetWithBlend(TargetActor, 1, VTBlend_Cubic);
}

void UTHNCameraManagerSubsystem::ReturnToDefaultCamera(ATHNPlayerController* PlayerController)
{
	PlayerController->SetViewTargetWithBlend(Cast<ATHNPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)), 1, VTBlend_Cubic);
}

void UTHNCameraManagerSubsystem::RegisterPlayerCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("Registering Player Camera"))
}
