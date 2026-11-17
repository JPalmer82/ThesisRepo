// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Features/Characters/THNPlayerCharacter.h"

#include "Components/SphereComponent.h"
#include "THNGrabSphereComponent.generated.h"

/**
 * 
 */
UCLASS()
class UTHNGrabSphereComponent : public USphereComponent
{
	GENERATED_BODY()

private:

	UFUNCTION()
	virtual void BeginPlay() override;
	
	UFUNCTION() 
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() 
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	//need a reference to the OwnerEnemy this is attached to as well as their anim instance

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Owner Enemy")
	class ATHNPossessableCharacter* OwnerEnemy = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	ATHNPlayerCharacter* PlayerCharacter = nullptr;
};
