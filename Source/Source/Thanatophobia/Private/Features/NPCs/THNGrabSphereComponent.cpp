// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/NPCs/THNGrabSphereComponent.h"

void UTHNGrabSphereComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UTHNGrabSphereComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UTHNGrabSphereComponent::OnOverlapEnd);
}

void UTHNGrabSphereComponent::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Tell Owner and OtherActor's animinstances to play the grab animation of whatever is grabbing the player
}

void UTHNGrabSphereComponent::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

}
