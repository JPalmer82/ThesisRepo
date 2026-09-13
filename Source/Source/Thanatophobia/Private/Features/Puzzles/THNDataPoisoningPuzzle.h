// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Services/Interfaces/THNInteractableInterface.h"
#include "THNDataPoisoningPuzzle.generated.h"

class UTHNPuzzleInfoComponent;
class USceneComponent;
class UCameraComponent;
class UStaticMeshComponent;
class UWidgetInteractionComponent;
class UTHNPlayerCameraService;
class UBoxComponent;
class UWidgetComponent;
class USceneCaptureComponent2D;

UCLASS()
class ATHNDataPoisoningPuzzle : public AActor, public ITHNInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATHNDataPoisoningPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(AActor* InitiatorActor) override;
	virtual void OnInteractEnd(AActor* InitiatorActor) override;
	
	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractionCollider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* UISceneCapture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* Widget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetInteractionComponent* WidgetInteractionComponent;
	
	//Puzzle Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle Settings")
	FVector2D RelativeScreenSize = FVector2D(620, 523);
	
private:
	class UTHNCameraManagerSubsystem* CameraSubsystem;
};
