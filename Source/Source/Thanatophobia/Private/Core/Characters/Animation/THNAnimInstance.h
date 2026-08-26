// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "THNAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UTHNAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsAiming = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsFiring = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsDead = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsReloading = false;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsMoving() const { return Speed != 0.0f; }

	UFUNCTION(BlueprintCallable, Category = "Animation", meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsNotMoving() const { return Speed == 0.0f; }

private:
	UPROPERTY()
	class ACharacter* OwnerCharacter;

	UPROPERTY() 
	class UCharacterMovementComponent* OwnerCharacterMovementComponent;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	float Speed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float FwdSpeed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float RightSpeed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float YawSpeed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float SmoothedYawSpeed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess))
	float SmoothYawSpeedLerpRate = 4.0f;

	FRotator PrevBodyRotation;
};
