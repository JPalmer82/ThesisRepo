// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/Characters/Animation/THNStopMontageNotify.h"

#include "THNAnimInstance.h"
#include "Features/Characters/THNPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UTHNStopMontageNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//ACharacter* buh = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//Cast<ATHNPlayerCharacter>(buh)->StopAllMontages();

	ATHNPlayerCharacter* buh = Cast<ATHNPlayerCharacter>(MeshComp->GetOwner());
	buh->StopAllMontages();
	UE_LOG(LogTemp, Warning, TEXT("Owner is: %s"), *buh->GetName());
}
