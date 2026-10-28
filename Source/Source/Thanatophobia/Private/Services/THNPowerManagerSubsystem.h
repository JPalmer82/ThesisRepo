// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "THNPowerManagerSubsystem.generated.h"

UENUM(BlueprintType)
enum EPoweredRooms
{
	Office,
	Experimentation,
	ResearchAndDevelopment,
	Security,
	RoomCount
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTHNOfficePowerActivatedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTHNOfficePowerDeactivatedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTHNExperimentationPowerActivatedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTHNExperimentationPowerDeactivatedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTHNRnDPowerActivatedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTHNRnDPowerDeactivatedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTHNSecurityPowerActivatedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTHNSecurityPowerDeactivatedDelegate);

class ATHNPowerDistributor;

UCLASS()
class UTHNPowerManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UTHNPowerManagerSubsystem();
	
	void RegisterPowerManager(TObjectPtr<ATHNPowerDistributor> PowerDistributorToRegister);
	void HandlePowerSlotUpdated(TObjectPtr<ATHNPowerDistributor> Activator, EPoweredRooms RoomToHandle);
	
	//Office
	UPROPERTY(BlueprintAssignable)
	FTHNOfficePowerActivatedDelegate OnOfficePowerActivated;
	UPROPERTY(BlueprintAssignable)
	FTHNOfficePowerDeactivatedDelegate OnOfficePowerDeactivated;
	
	//Experimentation
	UPROPERTY(BlueprintAssignable)
	FTHNExperimentationPowerActivatedDelegate OnExperimentationPowerActivated;
	UPROPERTY(BlueprintAssignable)
	FTHNExperimentationPowerDeactivatedDelegate OnExperimentationPowerDeactivated;
	
	//Research and Development
	UPROPERTY(BlueprintAssignable)
	FTHNRnDPowerActivatedDelegate OnRnDPowerActivated;
	UPROPERTY(BlueprintAssignable)
	FTHNRnDPowerDeactivatedDelegate OnRnDPowerDeactivated;
	
	//Security
	UPROPERTY(BlueprintAssignable)
	FTHNRnDPowerActivatedDelegate OnSecurityPowerActivated;
	UPROPERTY(BlueprintAssignable)
	FTHNRnDPowerDeactivatedDelegate OnSecurityPowerDeactivated;
	
	bool TryRemovePowerCell();
	bool TryAddPowerCell();
	
private:
	UPROPERTY()
	TObjectPtr<ATHNPowerDistributor> PowerDistributor = nullptr;
	
	UPROPERTY()
	TArray<bool> RoomStates;
	
	int MaxPowerCells = 3;
	int PowerCellCount = 0;
};
