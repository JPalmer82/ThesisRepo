// Fill out your copyright notice in the Description page of Project Settings.


#include "Features/AI/THNAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

ATHNAIController::ATHNAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1200.0f;

	SightConfig->SetMaxAge(5.0f);

	SightConfig->PeripheralVisionAngleDegrees = 90.0f;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ATHNAIController::TargetPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &ATHNAIController::TargetForgotten);
}

void ATHNAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void ATHNAIController::TargetPerceptionUpdated(AActor* Target, FAIStimulus Stimulus)
{
	UBlackboardComponent* BB = GetBlackboardComponent();

	if (!BB)
		return;

	if (Stimulus.WasSuccessfullySensed())
	{
		if (!GetCurrentTarget())
		{
			SetCurrentTarget(Target);
			BB->SetValueAsBool(HasSeenPlayerKeyName, true);
		}
	}
	else
	{
		if (GetCurrentTarget() == Target)
		{
			// Save location where vision was lost
			BB->SetValueAsVector(LastSeenLocationName, Target->GetActorLocation());
			SetCurrentTarget(nullptr);

			// Clear Target and set bHasSeenPlayer to false
			BB->SetValueAsBool(HasSeenPlayerKeyName, false);
		}
	}
}

void ATHNAIController::SetCurrentTarget(AActor* Target)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (Target)
		{
			BlackboardComponent->SetValueAsObject(TargetBlackboardKeyName, Target);
		}
		else
		{
			BlackboardComponent->ClearValue(TargetBlackboardKeyName);
		}
	}
}

UObject* ATHNAIController::GetCurrentTarget() const
{
	if (const UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		return BlackboardComponent->GetValueAsObject(TargetBlackboardKeyName);
	}

	return nullptr;
}

void ATHNAIController::TargetForgotten(AActor* ForgottenTarget)
{
	UBlackboardComponent* BB = GetBlackboardComponent();

	if (GetCurrentTarget() == ForgottenTarget)
	{
		SetCurrentTarget(nullptr);
		BB->SetValueAsBool(HasSeenPlayerKeyName, false);
	}
}

void ATHNAIController::DisableAndClearPerceptions()
{
	for (auto PerceptionConfigIter = AIPerceptionComponent->GetSensesConfigIterator();
		PerceptionConfigIter;
		++PerceptionConfigIter)
	{
		AIPerceptionComponent->SetSenseEnabled((*PerceptionConfigIter)->GetSenseImplementation(), false);
	}

	for (auto TargetPerceptualData = AIPerceptionComponent->GetPerceptualDataIterator();
		TargetPerceptualData;
		++TargetPerceptualData)
	{
		for (FAIStimulus& Stimuli : TargetPerceptualData->Value.LastSensedStimuli)
		{
			Stimuli.SetStimulusAge(TNumericLimits<float>::Max());
		}
	}

	SetCurrentTarget(nullptr);
}

void ATHNAIController::EnablePerceptions()
{
	for (auto PerceptionConfigIter = AIPerceptionComponent->GetSensesConfigIterator();
		PerceptionConfigIter;
		++PerceptionConfigIter)
	{
		AIPerceptionComponent->SetSenseEnabled((*PerceptionConfigIter)->GetSenseImplementation(), true);
	}
}
