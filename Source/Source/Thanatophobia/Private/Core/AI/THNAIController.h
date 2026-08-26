// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "THNAIController.generated.h"

/**
 * 
 */
UCLASS()
class ATHNAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	class UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;
};
