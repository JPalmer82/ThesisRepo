#include "THNPossessableActorComponent.h"
#include "THNPossessableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Core/AI/THNAIController.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Core/Characters/Animation/THNAnimInstance.h"

// Sets default values for this component's properties
UTHNPossessableActorComponent::UTHNPossessableActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTHNPossessableActorComponent::AttachDroneToSocket()
{
	for (AActor* Drone : DebugDrones)
	{
		if (IsValid(Drone))
			GetWorld()->DestroyActor(Drone);
	}

	for (TObjectPtr<USkeletalMeshSocket> Socket : ActivePossessionSockets)
	{
		AActor* NewDrone = GetWorld()->SpawnActor(DebugDroneBlueprint);
		bDoesDroneExist = true;
		ATHNPossessableCharacter* ThisEnemy = Cast<ATHNPossessableCharacter>(GetOwner());
		ATHNAIController* EnemyAI = ThisEnemy->GetController<ATHNAIController>();
		if (EnemyAI)
		{
			if (EnemyAI->GetBlackboardComponent())
			{
				EnemyAI->GetBlackboardComponent()->SetValueAsBool("bIsPossessed", true);
			}
		}
		USkeletalMeshComponent* OwnerMesh = ThisEnemy->GetMesh();
		OwnerAnimInstance = Cast<UTHNAnimInstance>(OwnerMesh->GetAnimInstance());
		OwnerProbeAnimInstance = Cast<UTHNAnimInstance>(ThisEnemy->GetProbeAnimInstance());
		OwnerAnimInstance->IsDead = false;
		OwnerProbeAnimInstance->IsDead = false;
		FAttachmentTransformRules AttachmentRules (EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
		FName SocketName = Socket->SocketName;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *SocketName.ToString())
		NewDrone->AttachToComponent(GetOwner()->GetComponentByClass<USkeletalMeshComponent>(), AttachmentRules, SocketName);
		
		DebugDrones.Add(NewDrone);
	}
}

void UTHNPossessableActorComponent::RandomizePossessionPosition()
{
	FlushPersistentDebugLines(GetWorld());
	ActivePossessionSockets.Empty();
	
	AActor* OwnerActor = GetOwner();
	USkeletalMeshComponent* SkeletalMeshComp = OwnerActor->GetComponentByClass<USkeletalMeshComponent>();

	if (PossessionSockets.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("You must be in play mode to call this function!"))
		return;
	}
	
	for (int i = 0; i < NumActiveDronesInBody; i++)
		ActivePossessionSockets.Add(PossessionSockets[FMath::RandRange(0, PossessionSockets.Num() - 1)]);
	
	AttachDroneToSocket();
}

void UTHNPossessableActorComponent::ClearPossessionPositions()
{
	ActivePossessionSockets.Empty();
	
	for (AActor* Drone : DebugDrones)
	{
		if (IsValid(Drone))
			GetWorld()->DestroyActor(Drone);
	}

	DebugDrones.Empty();
}

bool UTHNPossessableActorComponent::DoesDroneExist()
{
	if (ActivePossessionSockets.Num() == 0)
	{
		return bDoesDroneExist = false;
	}
	else
	{
		return bDoesDroneExist = true;
	}
}

void UTHNPossessableActorComponent::InitializePossessionSockets()
{
	AActor* OwnerActor = GetOwner();
	USkeletalMeshComponent* SkeletalMeshComp = OwnerActor->GetComponentByClass<USkeletalMeshComponent>();
	TArray<TObjectPtr<USkeletalMeshSocket>> MeshSockets = SkeletalMeshComp->GetSkeletalMeshAsset()->GetSkeleton()->Sockets;
	
	for (TObjectPtr<USkeletalMeshSocket> Socket : MeshSockets)
	{
		if (Socket->SocketName.ToString().Contains(PossessionSocketName.ToString(), ESearchCase::IgnoreCase, ESearchDir::FromStart))
		{
			PossessionSockets.Add(Socket);
		}
	}
}

// Called when the game starts
void UTHNPossessableActorComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializePossessionSockets();
}

// Called every frame
// void UTHNDronePossessionActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
// }