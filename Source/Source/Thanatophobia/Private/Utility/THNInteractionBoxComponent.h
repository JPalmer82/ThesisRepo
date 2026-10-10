// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Services/Interfaces/THNInteractableInterface.h"
#include "THNInteractionBoxComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTHNInteractBoxDelegate, AActor*, InitiatorActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTHNInteractEndBoxDelegate, AActor*, InitiatorActor);

UCLASS()
class UTHNInteractionBoxComponent : public UBoxComponent, public ITHNInteractableInterface
{
	GENERATED_BODY()

	explicit UTHNInteractionBoxComponent(const FObjectInitializer& Initializer);
	
public:
	UPROPERTY(BlueprintAssignable)
	FTHNInteractBoxDelegate OnBoxInteract;	
	
	UPROPERTY(BlueprintAssignable)
	FTHNInteractEndBoxDelegate OnBoxInteractEnd;
	
	virtual void OnInteract(AActor* InitiatorActor) override;
	virtual void OnInteractEnd(AActor* InitiatorActor) override;
};
