// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/THNServiceLocator.h"

//Define the static container
TMap<FName, UObject*> UTHNServiceLocator::Services;

void UTHNServiceLocator::RegisterService(const FName ServiceName, UObject* Service)
{
	if (Service)
	{
		Services.Add(ServiceName, Service);
	}
}

void UTHNServiceLocator::UnregisterService(const FName ServiceName)
{
	Services.Remove(ServiceName);
}

void UTHNServiceLocator::ClearServices()
{
	Services.Empty();
}
