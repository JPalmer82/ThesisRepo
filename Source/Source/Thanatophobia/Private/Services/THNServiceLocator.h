// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "THNServiceLocator.generated.h"

// Global registry for game-wide services, enabling other parts of the game 
// to retrieve those services on demand
// This is the core of the Service Locator pattern implementation
UCLASS()
class UTHNServiceLocator : public UObject
{
	GENERATED_BODY()
	
private:
	// A static map that holds all registered services
	//UPROPERTY(Transient)
	static TMap<FName, UObject*> Services;
	
public:
	// Template function that retrieves a service by name
	// and attempts to cast it to the requested type
	// Returns nullptr if the service isn't found or cast fails
	//TODO: Search through services by type instead of by name
	template <typename T>
	static T* GetService(const FName ServiceName)
	{
		UObject** FoundService = Services.Find(ServiceName);
		return FoundService ? Cast<T>(*FoundService) : nullptr;
	}
	
	//Registers a service instance under the specified name
	UFUNCTION(BlueprintCallable, Category = "Services")
	static void RegisterService(const FName ServiceName, UObject* Service);
	
	//Unregisters a service by its name, removing it from the registry
	UFUNCTION(BlueprintCallable, Category = "Services")
	static void UnregisterService(const FName ServiceName);
	
	//Clears all registered services from the locator
	//Typically called during game shutdown
	UFUNCTION(BlueprintCallable, Category = "Services")
	static void ClearServices();
};
