// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Features/Characters/THNPlayerCharacter.h"
#include "THNBullet.generated.h"

class UTHNInteractionBoxComponent;

UCLASS()
class ATHNBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHNBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY()
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UTHNInteractionBoxComponent> InteractionBox;

	UFUNCTION()
	void OnInteract(AActor* InitiatorActor);
};
