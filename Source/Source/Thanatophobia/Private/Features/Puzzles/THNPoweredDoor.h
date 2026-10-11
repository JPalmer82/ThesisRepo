// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THNPoweredDoor.generated.h"

enum EPoweredRooms : int;

UCLASS()
class ATHNPoweredDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHNPoweredDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true, ToolTip="The room that this door will open when powered"))
	TEnumAsByte<EPoweredRooms> ConnectedRoom;
	
	UFUNCTION()
	void OpenDoor();
	
	UFUNCTION()
	void CloseDoor();
};
