// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Features/Puzzles/THNNeuronPuzzleManager.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "THNPlayerCharacter.generated.h"

enum class EGameState;
class UTHNGameInstance;
class UInputAction;
class UCameraComponent;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
class USpringArmComponent;
class UTHNAnimInstance;
struct FInputActionValue;
class UTHN_PauseMenuWidget;

UCLASS()
class THANATOPHOBIA_API ATHNPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATHNPlayerCharacter();
	virtual void PawnClientRestart() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCameraComponent* CameraComponent;

	// These 3 UFUNCTIONS are empty functions that get called but are utilized for blueprint connections on Mika
	UFUNCTION(BlueprintImplementableEvent)
	void PopOutCylinder();

	UFUNCTION(BlueprintImplementableEvent)
	void RotateCylinderClockwise();

	UFUNCTION(BlueprintImplementableEvent)
	void RotateCylinderCounterClockwise();

	UTHNAnimInstance* GetWorldSpaceAnimInstance() const {return WorldSpaceAnimInstance;}
	UTHNAnimInstance* GetBaseAnimInstance() const {return BaseMeshAnimInstance;}

	void StopAllMontages();
private:
	UFUNCTION()
	void OnGameStateChanged(EGameState PreviousGameState, EGameState NewGameState);
	UTHNGameInstance* GameInstance;
	
	UPROPERTY(EditDefaultsOnly, Category="Rendering")
	USkeletalMeshComponent* WorldSpaceSkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float MaxSprintSpeed = 800;
	float MaxWalkSpeed = 600;

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* CrouchMontage;

	UPROPERTY()
	UTHNAnimInstance* WorldSpaceAnimInstance;

	UPROPERTY()
	UTHNAnimInstance* BaseMeshAnimInstance;

	UPROPERTY()
	UAIPerceptionStimuliSourceComponent* StimuliSource;
	
	/*****************************************************/
	/*                      Input                        */
	/*****************************************************/
	
	UPROPERTY()
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem;
	
	//Mapping Contexts
	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputMappingContext* MovementInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputMappingContext* ReloadInputMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputMappingContext* PuzzleInputMappingContext;

	//Base Context Actions
	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* MoveInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* LookInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* CrouchInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* SprintInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* AimInputAction;
	
	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* ShootInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* EquipTerminalInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* StartReloadInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* InteractInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* PauseInputAction;

	//Reload Actions
	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* StopReloadInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* LoadBulletInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* CycleCylinderLeftInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* CycleCylinderRightInputAction;

	//Incubator Puzzle
	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* ChangeColorRedInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* ChangeColorGreenInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* ChangeColorBlueInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* RotateHorizontalInputAction;

	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* RotateVerticalInputAction;
	
	//Office Puzzle
	UPROPERTY(EditAnywhere, Category = "Controls")
	UInputAction* ClickInputAction;
	
	//Revolver
	UPROPERTY(EditAnywhere, Category="Reload")
	UStaticMeshComponent* RevolverReloadPosition;
	
	UPROPERTY(EditAnywhere, Category = "Reload")
	UStaticMeshComponent* ReloadLookPosition;

	UPROPERTY(EditAnywhere, Category = "Reload")
	FRotator CachedReloadPosition;

	UPROPERTY(EditAnywhere, Category = "Probe")
	UStaticMeshComponent* ProbePoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Probe", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Probe;

	UPROPERTY(EditAnywhere, Category = "Probe")
	UStaticMeshComponent* RestProbePosition;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* RevolverComponent;

	UPROPERTY(EditAnywhere, Category="Revolver")
	USceneComponent* RevolverBasePosition;


	UPROPERTY(EditAnywhere, Category = "Probe")
	bool bIsProbeEquipped;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* ProbeMontage;

	/*****************************************************/
	/*                      Shooting                     */
	/*****************************************************/

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float LineTraceDistance = 5000.0f;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	int CurrentBulletIndex = 0;

	bool BulletChambers[6] = { true, true, true, true, true, true };

	/*****************************************************/
	/*                    Pause Menu                     */
	/*****************************************************/

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTHN_PauseMenuWidget> PauseMenuWidgetClass;

	UTHN_PauseMenuWidget* PauseMenuWidget;

private:
	//Base Context
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	void HandleLookInput(const FInputActionValue& InputActionValue);
	void HandleCrouchInput(const FInputActionValue& InputActionValue);
	void HandleSprintInputStart(const FInputActionValue& InputActionValue);
	void HandleSprintInputEnd(const FInputActionValue& InputActionValue);
	void HandleAimStartInput(const FInputActionValue& InputActionValue);
	void HandleAimEndInput(const FInputActionValue& InputActionValue);
	void HandleShootInput(const FInputActionValue& InputActionValue);
	void HandleProbeInputStart(const FInputActionValue& InputActionValue);
	void HandleProbeInputEnd(const FInputActionValue& InputActionValue);
	void HandleReloadStartInput(const FInputActionValue& InputActionValue);
	void HandleInteractInput(const FInputActionValue& InputActionValue);

	void TogglePause(const FInputActionValue& InputActionValue);

	//Reload Context
	void HandleReloadEndInput(const FInputActionValue& InputActionValue);
	void HandleLoadBulletInput(const FInputActionValue& InputActionValue);
	void HandleCycleCylinderLeftInput(const FInputActionValue& InputActionValue);
	void HandleCycleCylinderRightInput(const FInputActionValue& InputActionValue);

	//Incubator Puzzle
	void HandleChangeColorRedInput(const FInputActionValue& InputActionValue);
	void HandleChangeColorGreenInput(const FInputActionValue& InputActionValue);
	void HandleChangeColorBlueInput(const FInputActionValue& InputActionValue);
	void HandlePuzzleRotateHorizontalStartInput(const FInputActionValue& InputActionValue);
	void HandlePuzzleRotateHorizontalEndInput(const FInputActionValue& InputActionValue);
	void HandlePuzzleRotateVerticalStartInput(const FInputActionValue& InputActionValue);
	void HandlePuzzleRotateVerticalEndInput(const FInputActionValue& InputActionValue);
	
	//Office Puzzle
	void HandleClickInput(const FInputActionValue& InputActionValue);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	AActor* CurrentInteractActor;
	bool IsInteracting = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UCameraComponent* GetCameraComponent() const { return CameraComponent; };
	void SwitchToMappingContext(UInputMappingContext* NewInputMappingContext);

	UPROPERTY(BlueprintReadWrite)
	EIncubatorPuzzleColor CurrentIncubatorColor = EIncubatorPuzzleColor::None;

	UPROPERTY(BlueprintReadWrite)
	bool IsRotatingPuzzle = false;

	UPROPERTY(BlueprintReadWrite)
	FVector2D RotateInputVector;
};
