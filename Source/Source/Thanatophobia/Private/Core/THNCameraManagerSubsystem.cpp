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
	AActor* CurrentViewTarget = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewTarget();
	UCameraComponent* CurrentCamera = Cast<UCameraComponent>(CurrentViewTarget->GetComponentByClass(UCameraComponent::StaticClass()));
	
	CachedAccumulatedLookInput = AccumulatedLookIinput;
	AccumulatedLookIinput += FVector2D(LookInput.X, -LookInput.Y);
	
	FVector2D OutPolar;
	FMath::CartesianToPolar(AccumulatedLookIinput, OutPolar);
	OutPolar.X = FMath::Clamp(OutPolar.X, -80, 80);
	FMath::PolarToCartesian(OutPolar, AccumulatedLookIinput);

	FRotator Rot = FRotator(AccumulatedLookIinput.Y - CachedAccumulatedLookInput.Y, AccumulatedLookIinput.X - CachedAccumulatedLookInput.X, 0);
	CurrentCamera->AddRelativeRotation(Rot);
}

void UTHNCameraManagerSubsystem::LookAtTargetWithRadius(ATHNPlayerController* PlayerController, AActor* TargetActor,
	float Radius)
{
	PlayerController->SetViewTargetWithBlend(TargetActor, 1, VTBlend_Cubic);
	UCameraComponent* CurrentCamera = Cast<UCameraComponent>(TargetActor->GetComponentByClass(UCameraComponent::StaticClass()));
	CachedViewTargetForward = CurrentCamera->GetForwardVector();
	CachedViewTarget = TargetActor;
	AccumulatedLookIinput = FVector2D(0.0f, 0.0f);
}

void UTHNCameraManagerSubsystem::ReturnToDefaultCamera(ATHNPlayerController* PlayerController)
{
	PlayerController->SetViewTargetWithBlend(Cast<ATHNPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)), 1, VTBlend_Cubic);
	UCameraComponent* CurrentCamera = Cast<UCameraComponent>(CachedViewTarget->GetComponentByClass(UCameraComponent::StaticClass()));
	FQuat AngleBetween = FQuat::FindBetweenVectors(CurrentCamera->GetForwardVector(), CachedViewTargetForward);
}

void UTHNCameraManagerSubsystem::RegisterPlayerCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("Registering Player Camera"))
}

float UTHNCameraManagerSubsystem::GetAngleBetweenVectors(FVector vec1, FVector vec2)
{
	vec1.Normalize();
	vec2.Normalize();
	
	float dot = FVector::DotProduct(vec1, vec2);
	return (acos(dot) * 180) / PI;
}
