// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/THNInteractableInterface.h"
#include "GameFramework/Pawn.h"
#include "THNIncubator.generated.h"

class UInputMappingContext;

UCLASS()
class ATHNIncubator : public APawn, public ITHNInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATHNIncubator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnInteract(AActor* InitiatorActor) override;
	virtual void OnInteractEnd(AActor* InitiatorActor) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeToIncubatorCamera(AActor* PlayerCharacter);
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeToPlayerCamera(AActor* PlayerCharacter);
	UFUNCTION(BlueprintImplementableEvent)
	void CallNeuronTrace(AActor* PlayerCharacter);

private:
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* IncubatorMappingContext;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* DefaultMappingContext;
};
