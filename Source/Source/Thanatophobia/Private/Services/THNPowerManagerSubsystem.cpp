// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/THNPowerManagerSubsystem.h"

UTHNPowerManagerSubsystem::UTHNPowerManagerSubsystem()
{
	
	for (int i = 0; i < EPoweredRooms::RoomCount; i++)
	{
		RoomStates.Add(false);
		if (i == EPoweredRooms::ResearchAndDevelopment)
		{
			RoomStates[i] = true;
		}
	}
}

void UTHNPowerManagerSubsystem::RegisterPowerManager(TObjectPtr<ATHNPowerDistributor> PowerDistributorToRegister)
{
	if (PowerDistributor != nullptr)
		return;
	
	PowerDistributor = PowerDistributorToRegister;
}

void UTHNPowerManagerSubsystem::HandlePowerSlotUpdated(TObjectPtr<ATHNPowerDistributor> Activator, EPoweredRooms RoomToHandle)
{
	if (PowerDistributor != nullptr && PowerDistributor == Activator)
	{
		if (!RoomStates[RoomToHandle])
		{
			if (!TryRemovePowerCell())
				return;
			
			switch (RoomToHandle)
			{
				case Office:
					OnOfficePowerActivated.Broadcast();
					break;
				case Experimentation:
					OnExperimentationPowerActivated.Broadcast();
					break;
				case ResearchAndDevelopment:
					OnRnDPowerActivated.Broadcast();
					break;
				case Security:
					OnSecurityPowerActivated.Broadcast();
					break;
				default:
					UE_LOG(LogTemp, Error, TEXT("THN: No valid OnPowerActivated delegate found!"))
			}

			RoomStates[RoomToHandle] = true;
		}
		else
		{
			if (!TryAddPowerCell())
				return;
			
			switch (RoomToHandle)
			{
				case Office:
					OnOfficePowerDeactivated.Broadcast();
					break;
				case Experimentation:
					OnExperimentationPowerDeactivated.Broadcast();
					break;
				case ResearchAndDevelopment:
					OnRnDPowerDeactivated.Broadcast();
					break;
				case Security:
					OnSecurityPowerDeactivated.Broadcast();
					break;
				default:
					UE_LOG(LogTemp, Error, TEXT("THN: No valid OnPowerDeactivated delegate found!"))
			}
			
			RoomStates[RoomToHandle] = false;
		}
	}
}

bool UTHNPowerManagerSubsystem::TryRemovePowerCell()
{
	if (PowerCellCount <= 0)
		return false;
	
	PowerCellCount--;
	UE_LOG(LogTemp, Warning, TEXT("PowerCells: %d"), PowerCellCount);
	return true;
}

bool UTHNPowerManagerSubsystem::TryAddPowerCell()
{
	if (PowerCellCount == MaxPowerCells)
		return false;
	
	PowerCellCount++;
	UE_LOG(LogTemp, Warning, TEXT("PowerCells: %d"), PowerCellCount);
	return true;
}
