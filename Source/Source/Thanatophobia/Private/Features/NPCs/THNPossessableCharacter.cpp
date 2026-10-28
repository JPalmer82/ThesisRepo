// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/NPCs/THNPossessableCharacter.h"
#include "Features/Characters/Animation/THNAnimInstance.h"

#include "Core/THNAIManagerSubsystem.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"

// Sets default values
ATHNPossessableCharacter::ATHNPossessableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMeshComponent* BaseMesh = GetComponentByClass<USkeletalMeshComponent>();
	if (BaseMesh)
	{
		BaseMesh->bVisibleInSceneCaptureOnly = false;
		BaseMesh->bHiddenInSceneCapture = true;
		BaseMesh->SetCustomDepthStencilValue(4);
		BaseMesh->SetCustomDepthStencilWriteMask(ERendererStencilMask::ERSM_4);
	}
	
	ProbeViewMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ProbeViewMesh"));
	ProbeViewMesh->SetupAttachment(GetRootComponent());
	ProbeViewMesh->bHiddenInSceneCapture = false;
	ProbeViewMesh->bVisibleInSceneCaptureOnly = true;

	PerceptionStimulusComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("PerceptionStimulusComponent");
	PerceptionStimulusComponent->RegisterForSense(UAISense_Sight::StaticClass());
	PerceptionStimulusComponent->RegisterForSense(UAISense_Hearing::StaticClass());
}

// Called when the game starts or when spawned
void ATHNPossessableCharacter::BeginPlay()
{
	Super::BeginPlay();

	NPCAnimInstance = Cast<UTHNAnimInstance>(GetMesh()->GetAnimInstance());
	ProbeNPCAnimInstance = Cast<UTHNAnimInstance>(ProbeViewMesh->GetAnimInstance());
	NPCAnimInstance->IsDead = false;
	ProbeNPCAnimInstance->IsDead = false;

	PerceptionStimulusComponent->RegisterWithPerceptionSystem();

	UTHNAIManagerSubsystem* AIManager = GetGameInstance()->GetSubsystem<UTHNAIManagerSubsystem>();
	if (IsValid(AIManager))
	{
		AIManager->AIEnemies.Add(this);
		UE_LOG(LogTemp, Log, TEXT("Added %s to the AI Manager List"), *this->GetName())
	}
}

void ATHNPossessableCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UTHNAIManagerSubsystem* AIManager = GetGameInstance()->GetSubsystem<UTHNAIManagerSubsystem>();
	if (IsValid(AIManager))
	{
		AIManager->AIEnemies.Remove(this);
		UE_LOG(LogTemp, Log, TEXT("Removed %s to the AI Manager List"), *this->GetName())
	}
}

// Called every frame
void ATHNPossessableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATHNPossessableCharacter::SetPerceptionStimuliEnabled(bool bStimuliEnabled)
{
	if (bStimuliEnabled)
	{
		PerceptionStimulusComponent->RegisterWithPerceptionSystem();
	}
	else
	{
		PerceptionStimulusComponent->UnregisterFromPerceptionSystem();
	}
}

// Called to bind functionality to input
// void ATHNPossessableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
// }

