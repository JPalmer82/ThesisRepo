// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Features/UI/THNDataPoisoningWord.h"
#include "GameFramework/Actor.h"
#include "Services/Interfaces/THNInteractableInterface.h"
#include "THNDataPoisoningPuzzle.generated.h"

class UTHNInteractionBoxComponent;
class UTHNDataPoisoningWidget;
struct FDataPoisoningWord;
class UTHNPuzzleInfoComponent;
class USceneComponent;
class UCameraComponent;
class UStaticMeshComponent;
class UWidgetInteractionComponent;
class UTHNPlayerCameraService;
class UBoxComponent;
class UWidgetComponent;
class USceneCaptureComponent2D;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDataPoisoningPuzzleCompleteDelegate);

USTRUCT(Blueprintable)
struct FDataPoisoningPuzzleSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	int NumWordsPerPages = 28;
	int NumPages = 3;
	FVector2D RelativeScreenSize = FVector2D(620, 523);
};

UCLASS()
class ATHNDataPoisoningPuzzle : public AActor
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

	UFUNCTION()
	void OnInteract(AActor* InitiatorActor);
	UFUNCTION()
	void OnInteractEnd(AActor* InitiatorActor);
	
	void SelectWord(UTHNDataPoisoningWord* Word);
	void RefreshWordList();
	bool CheckPuzzleCompletion();
	void HandlePuzzleSucceeded();
	
	int GetNumNegativeWords() const { return TotalNumNegativeWords; }
	
	FOnDataPoisoningPuzzleCompleteDelegate OnDataPoisoningPuzzleComplete;
	
	UPROPERTY()
	TArray<UTHNDataPoisoningWord*> SelectedWords;
	
	FOnClickStartDelegate OnClickDelegate;
	
	UTHNDataPoisoningWidget* GetDataPoisoningWidget() const { return DataPoisoningWidget; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle Settings")
	FDataPoisoningPuzzleSettings Settings;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzle Settings")
	float NegativePercentageNeededToWin = .8f;
	
	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTHNInteractionBoxComponent* InteractionCollider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* UISceneCapture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* Widget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetInteractionComponent* WidgetInteractionComponent;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UDataTable> SentimentTable;
	
	UPROPERTY()
	TArray<FDataPoisoningWord> Words;
	
private:
	UPROPERTY()
	class UTHNCameraManagerSubsystem* CameraSubsystem;
	
	UPROPERTY()
	class UTHNDataPoisoningWidget* DataPoisoningWidget;
	
	int TotalNumNegativeWords = 0;
	int NumNegativeWordsSelected = 0;
	int NumPositiveWordsSelected = 0;
	
	UFUNCTION()
	void OnClick();
};
