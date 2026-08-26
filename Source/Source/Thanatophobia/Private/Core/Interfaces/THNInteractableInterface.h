// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "THNInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHNInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ITHNInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnInteract(AActor* InitiatorActor) = 0;
	virtual void OnInteractEnd(AActor* InitiatorActor) = 0;
};
