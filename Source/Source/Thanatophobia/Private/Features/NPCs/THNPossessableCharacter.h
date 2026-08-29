// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "THNPossessableCharacter.generated.h"

class UTHNAnimInstance;

UCLASS()
class ATHNPossessableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATHNPossessableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UTHNAnimInstance* GetNPCAnimInstance() { return NPCAnimInstance; }
	FORCEINLINE UTHNAnimInstance* GetProbeAnimInstance() { return ProbeNPCAnimInstance; }

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* ProbeViewMesh;

	UPROPERTY()
	UTHNAnimInstance* NPCAnimInstance;

	UPROPERTY()
	UTHNAnimInstance* ProbeNPCAnimInstance;
};
