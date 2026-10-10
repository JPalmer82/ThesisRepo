// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/Interfaces/THNInteractableInterface.h"
#include "GameFramework/Pawn.h"
#include "THNIncubator.generated.h"

class UTHNInteractionBoxComponent;
class UInputMappingContext;

UCLASS()
class ATHNIncubator : public APawn
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
	
	UFUNCTION()
	void OnInteract(AActor* InitiatorActor);
	
	UFUNCTION()
	void OnInteractEnd(AActor* InitiatorActor);

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
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UTHNInteractionBoxComponent> InteractionBox;
	
	UPROPERTY()
	TObjectPtr<USceneComponent> Root;
};
