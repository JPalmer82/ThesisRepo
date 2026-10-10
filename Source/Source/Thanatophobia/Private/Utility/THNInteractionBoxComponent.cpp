// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/THNInteractionBoxComponent.h"

#include "Source/Thanatophobia/Thanatophobia.h"

UTHNInteractionBoxComponent::UTHNInteractionBoxComponent(const FObjectInitializer& Initializer) : Super(Initializer)
{
	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionResponseToChannel(ECC_Interactable, ECR_Block);
}

void UTHNInteractionBoxComponent::OnInteract(AActor* InitiatorActor)
{
	OnBoxInteract.Broadcast(InitiatorActor);
}

void UTHNInteractionBoxComponent::OnInteractEnd(AActor* InitiatorActor)
{
	OnBoxInteractEnd.Broadcast(InitiatorActor);
}
