// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "THNGrabSphereComponent.generated.h"

/**
 * 
 */
UCLASS()
class UTHNGrabSphereComponent : public USphereComponent
{
	GENERATED_BODY()

	UFUNCTION()
	virtual void BeginPlay() override;
	
	UFUNCTION() 
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() 
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
