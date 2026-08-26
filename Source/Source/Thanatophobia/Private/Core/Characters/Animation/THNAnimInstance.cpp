// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/Animation/THNAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UTHNAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		OwnerCharacterMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UTHNAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnerCharacter)
	{
		FVector Velocity = OwnerCharacter->GetVelocity();
		Speed = Velocity.Length();

		FRotator BodyRotation = OwnerCharacter->GetActorRotation();

		FRotator RotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRotation, PrevBodyRotation);
		PrevBodyRotation = BodyRotation;

		YawSpeed = RotationDelta.Yaw / DeltaSeconds;
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, SmoothYawSpeedLerpRate);
	}
}
