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
	
	FVector CamForward = CurrentCamera->GetForwardVector();
	FVector NewForward = CurrentCamera->GetForwardVector();
	
	float AngleFromCenter = GetAngleBetweenVectors(CachedViewTargetForward, NewForward);
	//UE_LOG(LogTemp, Warning, TEXT("Rotator: %s"), *CurrentCamera->GetRelativeRotation().ToString());
	
	if (AngleFromCenter <= 55)
	{
		CurrentCamera->AddRelativeRotation(Rot);
	}
	
	//FVector ViewTargetLocation = CurrentViewTarget->GetActorLocation();
	//DrawDebugLine(GetWorld(), ViewTargetLocation, (ViewTargetLocation + CachedViewTargetForward) * 100, FColor::Red, false, 1);
	//DrawDebugLine(GetWorld(), ViewTargetLocation, (ViewTargetLocation + CamForward * 100), FColor::Green, false, 1);
}

void UTHNCameraManagerSubsystem::LookAtTargetWithRadius(ATHNPlayerController* PlayerController, AActor* TargetActor,
	float Radius)
{
	PlayerController->SetViewTargetWithBlend(TargetActor, 1, VTBlend_Cubic);
	UCameraComponent* CurrentCamera = Cast<UCameraComponent>(TargetActor->GetComponentByClass(UCameraComponent::StaticClass()));
	CachedViewTargetForward = CurrentCamera->GetForwardVector();
	CachedViewTarget = TargetActor;
}

void UTHNCameraManagerSubsystem::ReturnToDefaultCamera(ATHNPlayerController* PlayerController)
{
	PlayerController->SetViewTargetWithBlend(Cast<ATHNPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)), 1, VTBlend_Cubic);
	UCameraComponent* CurrentCamera = Cast<UCameraComponent>(CachedViewTarget->GetComponentByClass(UCameraComponent::StaticClass()));
	FQuat AngleBetween = FQuat::FindBetweenVectors(CurrentCamera->GetForwardVector(), CachedViewTargetForward);
	CurrentCamera->SetRelativeRotation(AngleBetween * CurrentCamera->GetRelativeRotation().Quaternion());
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
