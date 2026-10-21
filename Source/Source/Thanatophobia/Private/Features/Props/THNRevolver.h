// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "THNRevolver.generated.h"

UCLASS()
class ATHNRevolver : public AActor
{
	GENERATED_BODY()
	
	ATHNRevolver();
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TArray<TObjectPtr<UStaticMeshComponent>> BulletMeshes;
	
public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> RevolverMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnRevolverFired(TArray<bool>& BulletState);
};
