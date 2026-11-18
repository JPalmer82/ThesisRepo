// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/NPCs/THNGrabSphereComponent.h"
#include "THNPossessableCharacter.h"
#include "THNPossessableActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UTHNGrabSphereComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UTHNGrabSphereComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UTHNGrabSphereComponent::OnOverlapEnd);

	if (ATHNPlayerCharacter* tempPlayer = Cast<ATHNPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		PlayerCharacter = tempPlayer;
	}
}

void UTHNGrabSphereComponent::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Tell Owner and OtherActor's animinstances to play the grab animation of whatever is grabbing the player
	if (OtherActor == PlayerCharacter && IsValid(PlayerCharacter) && OwnerEnemy->GetComponentByClass<UTHNPossessableActorComponent>()->bDoesDroneExist)
	{
		PlayerCharacter->EnemyGrabbing = OwnerEnemy;

		OwnerEnemy->PlayEnemyGrabAnimation();
		OwnerEnemy->bIsGrabbing = true;
		PlayerCharacter->PlayGrabbedAnimation();
		PlayerCharacter->bHasBeenGrabbed = true;
	}
}

void UTHNGrabSphereComponent::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

}
