// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Props/THNRevolver.h"

#include "Core/THNGameInstance.h"
#include "Features/Characters/THNPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Services/THNGameManagerSubsystem.h"

// Sets default values
ATHNRevolver::ATHNRevolver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RevolverMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	RootComponent = RevolverMesh;
	
	for (int i = 0; i < 6; i++)
	{
		FString Name = FString::Printf(TEXT("Bullet_%d"), i);
		BulletMeshes.Add(CreateDefaultSubobject<UStaticMeshComponent>(*Name));
		
		FString SocketName = FString::Printf(TEXT("Socket_Bullet_%d"), i + 1);
		BulletMeshes[i]->SetupAttachment(RevolverMesh, *SocketName);
		
		BulletMeshes[i]->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	}
}

// Called when the game starts or when spawned
void ATHNRevolver::BeginPlay()
{
	Super::BeginPlay();
	
	ATHNPlayerCharacter* PlayerCharacter = Cast<ATHNPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->OnRevolverFired.AddUniqueDynamic(this, &ATHNRevolver::OnRevolverFired);
}

void ATHNRevolver::OnRevolverFired(TArray<bool>& BulletState)
{
	for (int i = 0; i < BulletState.Num(); i++)
	{
		BulletMeshes[i]->SetVisibility(BulletState[i]);
	}
}

