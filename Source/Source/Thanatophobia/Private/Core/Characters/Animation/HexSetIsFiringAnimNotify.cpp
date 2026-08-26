// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/Animation/HexSetIsFiringAnimNotify.h"

void UHexSetIsFiringAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	//UE_LOG(LogTemp, Warning, TEXT("ANIM NOTIFY"))
}
