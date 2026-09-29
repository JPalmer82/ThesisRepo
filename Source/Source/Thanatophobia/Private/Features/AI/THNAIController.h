// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "THNAIController.generated.h"

/**
 * 
 */
UCLASS()
class ATHNAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ATHNAIController();

	FORCEINLINE class UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly)
	FName TargetBlackboardKeyName = "Target";

	UPROPERTY(EditDefaultsOnly)
	FName LastSeenLocationName = "LastSeenLocation";

	UPROPERTY(EditDefaultsOnly)
	FName HasSeenPlayerName = "bHasSeenPlayer";

	UPROPERTY(EditDefaultsOnly)
	FName HeardLocationName = "HeardSoundLocation";

	UPROPERTY(EditDefaultsOnly)
	FName HasHeardSoundName = "bHasHeardSound";

	UPROPERTY(VisibleDefaultsOnly)
	class UAIPerceptionComponent* AIPerceptionComponent;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAISenseConfig_Hearing* HearingConfig;

private:

	UFUNCTION()
	void TargetPerceptionUpdated(AActor* Target, FAIStimulus Stimulus);

	void SetCurrentTarget(AActor* Target);

	UObject* GetCurrentTarget() const;

	UFUNCTION()
	void TargetForgotten(AActor* ForgottenTarget);

	void DisableAndClearPerceptions();
	void EnablePerceptions();
};
