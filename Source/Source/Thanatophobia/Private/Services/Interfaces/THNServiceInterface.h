// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "THNServiceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UTHNServiceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ITHNServiceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Called when the service is registered
	virtual void InitializeService() = 0;
	
	//Called when the service is unregistered or game ends
	virtual void ShutdownService() = 0;
};
