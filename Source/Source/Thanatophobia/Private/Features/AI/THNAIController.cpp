// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/AI/THNAIController.h"

void ATHNAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}