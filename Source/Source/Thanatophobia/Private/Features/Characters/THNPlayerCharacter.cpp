

#include "Features/Characters/THNPlayerCharacter.h"

#include "Kismet/KismetMathLibrary.h"

#include "Features/NPCs/THNDroneCharacter.h"

#include "Blueprint/UserWidget.h"
#include "Features/UI/THNPauseMenuWidget.h"

#include "Features/AI/THNAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/THNAnimInstance.h"
#include "Core/THNCameraManagerSubsystem.h"
#include "Core/THNGameInstance.h"
#include "Services/Interfaces/THNInteractableInterface.h"
#include "Features/NPCs/THNPossessableCharacter.h"
#include "Features/Puzzles/THNDataPoisoningPuzzle.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Features/Puzzles/THNNeuronPuzzleManager.h"
#include "Kismet/GameplayStatics.h"
#include "Source/Thanatophobia/Thanatophobia.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

// Sets default values
ATHNPlayerCharacter::ATHNPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetupAttachment(GetRootComponent());
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;

	WorldSpaceSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WorldSpaceSkeletalMeshComponent"));
	WorldSpaceSkeletalMeshComponent->SetupAttachment(GetMesh());
	WorldSpaceSkeletalMeshComponent->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetupAttachment(WorldSpaceSkeletalMeshComponent, TEXT("CameraSocket"));

	ReloadLookPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReloadCameraLookPosition")); //No longer needed
	ReloadLookPosition->SetupAttachment(GetRootComponent());
	
	RevolverReloadPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RevolverReloadPosition")); //No longer needed
	RevolverReloadPosition->SetupAttachment(GetRootComponent());

	RevolverBasePosition = CreateDefaultSubobject<USceneComponent>(TEXT("RevolverBasePosition")); //No longer needed
	RevolverBasePosition->SetupAttachment(CameraComponent);

	RevolverComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Revolver")); //No longer needed
	RevolverComponent->SetupAttachment(WorldSpaceSkeletalMeshComponent, TEXT("GunHoldPosition"));

	ProbePoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProbePoint"));
	ProbePoint->SetupAttachment(CameraComponent);

	RestProbePosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RestProbePosition"));
	RestProbePosition->SetupAttachment(WorldSpaceSkeletalMeshComponent);

	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));
	StimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
	StimuliSource->RegisterWithPerceptionSystem();

	bIsProbeEquipped = false;
	
	bUseControllerRotationYaw = true;
	
	//TODO: Remove this after implementing crouching with animation
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void ATHNPlayerCharacter::SwitchToMappingContext(UInputMappingContext* NewInputMappingContext)
{
	APlayerController* PlayerController = GetController<APlayerController>();

	if (IsValid(PlayerController))
	{
		EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (EnhancedInputSubsystem)
		{
			EnhancedInputSubsystem->ClearAllMappings();
			EnhancedInputSubsystem->AddMappingContext(NewInputMappingContext, 0);
		}
	}
}

void ATHNPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	
	SwitchToMappingContext(MovementInputMappingContext);
}

void ATHNPlayerCharacter::StopAllMontages()
{
	WorldSpaceAnimInstance->StopAllMontages(.2f);
	BaseMeshAnimInstance->StopAllMontages(.2f);
}

void ATHNPlayerCharacter::OnGameStateChanged(EGameState PreviousGameState, EGameState NewGameState)
{
	UE_LOG(LogTemp, Warning, TEXT("THN: New State: %s\n Old State: %s"), *UEnum::GetValueAsString(NewGameState), *UEnum::GetValueAsString(PreviousGameState));
	if (NewGameState == EGameState::Puzzle)
	{
		SwitchToMappingContext(PuzzleInputMappingContext);
	}
	else if (NewGameState == EGameState::Default)
	{
		SwitchToMappingContext(MovementInputMappingContext);
	}
}

// Called when the game starts or when spawned
void ATHNPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UTHNGameInstance* THNGameInstance = Cast<UTHNGameInstance>(GetGameInstance()))
	{
		GameInstance = THNGameInstance;
		GameInstance->OnGameStateChangedDelegate.AddUniqueDynamic(this, &ATHNPlayerCharacter::OnGameStateChanged);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get GameInstance!"))
	}
	
	WorldSpaceAnimInstance = Cast<UTHNAnimInstance>(WorldSpaceSkeletalMeshComponent->GetAnimInstance());
	BaseMeshAnimInstance = Cast<UTHNAnimInstance>(GetMesh()->GetAnimInstance());
	
	UTHNCameraManagerSubsystem* CameraSubsystem = GetGameInstance()->GetSubsystem<UTHNCameraManagerSubsystem>();
	UCameraComponent* CamComponent = Cast<UCameraComponent>(GetComponentByClass(UCameraComponent::StaticClass()));
	CameraSubsystem->OnPlayerInitialized.Execute(CamComponent);
}

// Called every frame
void ATHNPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATHNPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		//Base Context
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleMoveInput);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleLookInput);
		EnhancedInputComponent->BindAction(CrouchInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleCrouchInput);
		EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Started, this, &ATHNPlayerCharacter::HandleSprintInputStart);
		EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Completed, this, &ATHNPlayerCharacter::HandleSprintInputEnd);
		EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Canceled, this, &ATHNPlayerCharacter::HandleSprintInputEnd);
		EnhancedInputComponent->BindAction(InteractInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleInteractInput);
		
		EnhancedInputComponent->BindAction(AimInputAction, ETriggerEvent::Started, this, &ATHNPlayerCharacter::HandleAimStartInput);
		EnhancedInputComponent->BindAction(AimInputAction, ETriggerEvent::Completed, this, &ATHNPlayerCharacter::HandleAimEndInput);
		EnhancedInputComponent->BindAction(AimInputAction, ETriggerEvent::Canceled, this, &ATHNPlayerCharacter::HandleAimEndInput);
		
		EnhancedInputComponent->BindAction(ShootInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleShootInput);

		EnhancedInputComponent->BindAction(EquipTerminalInputAction, ETriggerEvent::Started, this, &ATHNPlayerCharacter::HandleProbeInputStart);
		EnhancedInputComponent->BindAction(EquipTerminalInputAction, ETriggerEvent::Completed, this, &ATHNPlayerCharacter::HandleProbeInputEnd);
		EnhancedInputComponent->BindAction(EquipTerminalInputAction, ETriggerEvent::Canceled, this, &ATHNPlayerCharacter::HandleProbeInputEnd);

		//Pause Context
		EnhancedInputComponent->BindAction(PauseInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::TogglePause);

		//Reload Context
		EnhancedInputComponent->BindAction(StartReloadInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleReloadStartInput);
		EnhancedInputComponent->BindAction(StopReloadInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleReloadEndInput);
		EnhancedInputComponent->BindAction(LoadBulletInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleLoadBulletInput);
		EnhancedInputComponent->BindAction(CycleCylinderLeftInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleCycleCylinderLeftInput);
		EnhancedInputComponent->BindAction(CycleCylinderRightInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleCycleCylinderRightInput);

		//Incubator Puzzle
		EnhancedInputComponent->BindAction(ChangeColorRedInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleChangeColorRedInput);
		EnhancedInputComponent->BindAction(ChangeColorGreenInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleChangeColorGreenInput);
		EnhancedInputComponent->BindAction(ChangeColorBlueInputAction, ETriggerEvent::Triggered, this, &ATHNPlayerCharacter::HandleChangeColorBlueInput);

		EnhancedInputComponent->BindAction(RotateHorizontalInputAction, ETriggerEvent::Started, this, &ATHNPlayerCharacter::HandlePuzzleRotateHorizontalStartInput);
		EnhancedInputComponent->BindAction(RotateHorizontalInputAction, ETriggerEvent::Completed, this, &ATHNPlayerCharacter::HandlePuzzleRotateHorizontalStartInput);
		EnhancedInputComponent->BindAction(RotateHorizontalInputAction, ETriggerEvent::Canceled, this, &ATHNPlayerCharacter::HandlePuzzleRotateHorizontalEndInput);

		EnhancedInputComponent->BindAction(RotateVerticalInputAction, ETriggerEvent::Started, this, &ATHNPlayerCharacter::HandlePuzzleRotateVerticalStartInput);
		EnhancedInputComponent->BindAction(RotateVerticalInputAction, ETriggerEvent::Completed, this, &ATHNPlayerCharacter::HandlePuzzleRotateVerticalStartInput);
		EnhancedInputComponent->BindAction(RotateVerticalInputAction, ETriggerEvent::Canceled, this, &ATHNPlayerCharacter::HandlePuzzleRotateVerticalEndInput);
		
		//Office Puzzle
		EnhancedInputComponent->BindAction(ClickInputAction, ETriggerEvent::Started, this, &ATHNPlayerCharacter::HandleClickInput);
	}
}

void ATHNPlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D MoveInput = InputActionValue.Get<FVector2D>();

	FVector RightVector = CameraComponent->GetRightVector();
	FVector ForwardVector = FVector::CrossProduct(RightVector, FVector::UpVector);

	AddMovementInput(RightVector * MoveInput.X + ForwardVector * MoveInput.Y);
}

void ATHNPlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	//TODO: Add IsCameraControllable bool in the Camera Service to check here
	FVector2D LookInput = InputActionValue.Get<FVector2D>();
	
	if (GameInstance->GetCurrentGameState() == EGameState::Default)
	{
		AddControllerYawInput(LookInput.X);
		AddControllerPitchInput(LookInput.Y);	
	}
	
	UTHNCameraManagerSubsystem* CameraSubsystem = GetGameInstance()->GetSubsystem<UTHNCameraManagerSubsystem>();
	CameraSubsystem->UpdateCamera(LookInput);
}

void ATHNPlayerCharacter::HandleCrouchInput(const FInputActionValue& InputActionValue)
{
	if (IsCrouched())
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void ATHNPlayerCharacter::HandleSprintInputStart(const FInputActionValue& InputActionValue)
{
	GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
}

void ATHNPlayerCharacter::HandleSprintInputEnd(const FInputActionValue& InputActionValue)
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

void ATHNPlayerCharacter::HandleAimStartInput(const FInputActionValue& InputActionValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Aiming down sights"));
	if (!bIsProbeEquipped)
	{
		//CameraComponent->FieldOfView = 60.0f;
		BaseMeshAnimInstance->IsAiming = true;
		WorldSpaceAnimInstance->IsAiming = true;
	}
}

void ATHNPlayerCharacter::HandleAimEndInput(const FInputActionValue& InputActionValue)
{
	//GEngine->AddOnScreenDebugMessage(-2, 5.f, FColor::Red, TEXT("Stopping aiming down sights"));
	//CameraComponent->FieldOfView = 90.0f;
	BaseMeshAnimInstance->IsAiming = false;
	WorldSpaceAnimInstance->IsAiming = false;
}

void ATHNPlayerCharacter::HandleShootInput(const FInputActionValue& InputActionValue)
{
	if (BaseMeshAnimInstance->IsFiring || WorldSpaceAnimInstance->IsFiring)
		return;
	
	if (CameraComponent && BulletChambers[CurrentBulletIndex] == true && !bIsProbeEquipped)
	{
		//UE_LOG(LogTemp, Error, TEXT("Firing, IsFiring is: %s"), BaseMeshAnimInstance->IsFiring ? TEXT("TRUE") : TEXT("FALSE"));
		BaseMeshAnimInstance->IsFiring = true;
		WorldSpaceAnimInstance->IsFiring = true;
		
		//GEngine->AddOnScreenDebugMessage(-3, 2.0f, FColor::Red, TEXT("Shooting"));
		FVector LineTraceStartPoint = CameraComponent->GetComponentLocation();
		FVector LineTraceEndPoint = LineTraceStartPoint + CameraComponent->GetForwardVector() * LineTraceDistance;

		FHitResult Hit;
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);

		bool bIsHit = GetWorld()->LineTraceSingleByChannel(Hit, LineTraceStartPoint, LineTraceEndPoint, ECC_Drone, TraceParams);

		//Handle Drone hit
		if (bIsHit)
		{
			AActor* HitActor = Hit.GetActor();

			if (IsValid(HitActor))
			{
				//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Hit: %s"), *Hit.GetActor()->GetName()));

				ATHNDroneCharacter* Drone = Cast<ATHNDroneCharacter>(Hit.GetActor());

				if (IsValid(Drone))
				{
					ATHNPossessableCharacter* DroneParent = Cast<ATHNPossessableCharacter>(Drone->GetAttachParentActor());
					if (IsValid(DroneParent))
					{
						UTHNAnimInstance* HitNPCAnimInstance = DroneParent->GetNPCAnimInstance();
						UTHNAnimInstance* HitProbeAnimInstance = DroneParent->GetProbeAnimInstance();
						HitNPCAnimInstance->IsDead = true;
						HitProbeAnimInstance->IsDead = true;
						DroneParent->GetMovementComponent()->StopActiveMovement();
					}
					Hit.GetActor()->Destroy();
					bIsHit = GetWorld()->LineTraceSingleByChannel(Hit, LineTraceStartPoint, LineTraceEndPoint, ECC_Pawn, TraceParams);
					if (bIsHit)
					{
						AActor* PatientHitActor = Hit.GetActor();
			
						if (IsValid(PatientHitActor))
						{
							//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
							//->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Hit: %s"), *Hit.GetActor()->GetName()));

							ATHNPossessableCharacter* Possessed = Cast<ATHNPossessableCharacter>(Hit.GetActor());
							if (IsValid(Possessed))
							{
								ATHNAIController* HitController = Possessed->GetController<ATHNAIController>();
								HitController->GetBlackboardComponent()->SetValueAsBool("bIsPossessed", false);
							}
						}
					}
				}
			}
		}

		
		//DrawDebugLine(GetWorld(), LineTraceStartPoint, LineTraceEndPoint, FColor::Red, false, 2.0f);

	}
	else
	{
		RotateCylinderClockwise();
	}

	BulletChambers[CurrentBulletIndex] = false;
	CurrentBulletIndex++;
	if (CurrentBulletIndex < 0)
	{
		CurrentBulletIndex = 5;
	}
	else if (CurrentBulletIndex > 5)
	{
		CurrentBulletIndex = 0;
	}	
	UE_LOG(LogTemp, Warning, TEXT("CurrentCylinder = %d"), CurrentBulletIndex)
}

void ATHNPlayerCharacter::HandleProbeInputStart(const FInputActionValue& InputActionValue)
{
	//GEngine->AddOnScreenDebugMessage(-4, 5.f, FColor::Yellow, TEXT("Equipping terminal"));
	bIsProbeEquipped = true;
	if (Probe) 
	{
		//Probe->SetWorldLocation(ProbePoint->GetComponentLocation());
		FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
		Probe->AttachToComponent(ProbePoint, AttachRules);

		BaseMeshAnimInstance->Montage_Play(ProbeMontage);
		WorldSpaceAnimInstance->Montage_Play(ProbeMontage);
	}
}

void ATHNPlayerCharacter::HandleProbeInputEnd(const FInputActionValue& InputActionValue)
{
	//GEngine->AddOnScreenDebugMessage(-5, 5.f, FColor::Yellow, TEXT("Unequipping terminal"));
	bIsProbeEquipped = false;
	if (Probe)
	{
		FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
		Probe->AttachToComponent(RestProbePosition, AttachRules);

		BaseMeshAnimInstance->Montage_Stop(.3, ProbeMontage);
		WorldSpaceAnimInstance->Montage_Stop(.3, ProbeMontage);
	}
}

void ATHNPlayerCharacter::HandleReloadStartInput(const FInputActionValue& InputActionValue)
{
	//You need to disable pawn control rotation here in order to move the camera for the reload
	//This will also be changed once we use animations for the reload
	CameraComponent->bUsePawnControlRotation = false;
	FRotator InitialCameraPosition = CameraComponent->GetRelativeRotation();
	CachedReloadPosition = InitialCameraPosition;
	SwitchToMappingContext(ReloadInputMappingContext);
	//UE_LOG(LogTemp, Warning, TEXT("Switching to reload"))
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Switching to reload"));
	BaseMeshAnimInstance->IsReloading = true;
	WorldSpaceAnimInstance->IsReloading = true;
	BaseMeshAnimInstance->Montage_Play(ReloadMontage);
	WorldSpaceAnimInstance->Montage_Play(ReloadMontage);
	if (BaseMeshAnimInstance->IsReloading)
	{
		PopOutCylinder();
	}

	for (bool& i : BulletChambers)
	{
		i = false;
	}

	//FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraComponent->GetComponentLocation(), ReloadLookPosition->GetComponentLocation());
	//UE_LOG(LogTemp, Warning, TEXT("LookAtRotation equals : %s"), *(LookAtRotation.ToString()))
	//CameraComponent->SetWorldRotation(LookAtRotation);

	//FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	//RevolverComponent->AttachToComponent(RevolverReloadPosition, AttachRules);
}

void ATHNPlayerCharacter::HandleInteractInput(const FInputActionValue& InputActionValue)
{
	if (IsInteracting && CurrentInteractActor != nullptr)
	{
		if (GameInstance->TrySwitchGameState(EGameState::Default))
		{
			Cast<ITHNInteractableInterface>(CurrentInteractActor)->OnInteractEnd(this);
			IsInteracting = false;
			return;	
		}
	}

	FVector LineTraceStartPoint = CameraComponent->GetComponentLocation();
	FVector LineTraceEndPoint = LineTraceStartPoint + CameraComponent->GetForwardVector() * LineTraceDistance;

	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	bool bIsHit = GetWorld()->LineTraceSingleByChannel(Hit, LineTraceStartPoint, LineTraceEndPoint, ECC_Pawn, TraceParams);
	//DrawDebugLine(GetWorld(), LineTraceStartPoint, LineTraceEndPoint, FColor::Red, false, 2.0f);
	
	if (bIsHit && Hit.GetActor())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *Hit.GetActor()->GetName());
		
		if (Cast<ITHNInteractableInterface>(Hit.GetActor()))
		{
			if (GameInstance->TrySwitchGameState(EGameState::Puzzle))
			{
				Cast<ITHNInteractableInterface>(Hit.GetActor())->OnInteract(this);
				CurrentInteractActor = Hit.GetActor();
				IsInteracting = true;
			}
		}
	}
}

void ATHNPlayerCharacter::TogglePause(const FInputActionValue& InputActionValue)
{
	if (!PauseMenuWidgetClass)
		return;

	//Check if game is paused
	bool bIsPaused = UGameplayStatics::IsGamePaused(GetWorld());
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	UE_LOG(LogTemp, Warning, TEXT("Player controller is %s"), *PlayerController->GetName())

	if (!bIsPaused)
	{
		//makes the pause menu widget if it does not already exist
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		if (!IsValid(PauseMenuWidget))
		{
			PauseMenuWidget = CreateWidget<UTHNPauseMenuWidget>(PlayerController, PauseMenuWidgetClass);
		}
		
		if (IsValid(PauseMenuWidget) && !PauseMenuWidget->IsInViewport())
		{
			PauseMenuWidget->AddToViewport();
		}

		//Allows player to select pause menu buttons
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(PauseMenuWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		if (PlayerController)
		{
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
	}
	else
	{
		if (IsValid(PauseMenuWidget))
		{
			//Unpauses game
			UGameplayStatics::SetGamePaused(GetWorld(), false);

			//resets input
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = false;

			//removes pause menu widget from screen
			PauseMenuWidget->RemoveFromParent();
		}
	}
}

void ATHNPlayerCharacter::HandleReloadEndInput(const FInputActionValue& InputActionValue)
{
	SwitchToMappingContext(MovementInputMappingContext);
	//UE_LOG(LogTemp, Warning, TEXT("Switching to base"))
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Switching to base"));
	CameraComponent->SetWorldRotation(CachedReloadPosition);
	
	//Need to reset the pawn control rotation after reload finishes
	CameraComponent->bUsePawnControlRotation = true;
	BaseMeshAnimInstance->IsReloading = false;
	WorldSpaceAnimInstance->IsReloading = false;

	BaseMeshAnimInstance->Montage_Play(ReloadMontage);
	WorldSpaceAnimInstance->Montage_Play(ReloadMontage);
	BaseMeshAnimInstance->Montage_JumpToSection("ReloadEnd", ReloadMontage);
	WorldSpaceAnimInstance->Montage_JumpToSection("ReloadEnd", ReloadMontage);

	if (!BaseMeshAnimInstance->IsReloading)
	{
		PopOutCylinder();
	}
	//FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	//RevolverComponent->AttachToComponent(RevolverBasePosition, AttachRules);
}

void ATHNPlayerCharacter::HandleLoadBulletInput(const FInputActionValue& InputActionValue)
{
	if (BulletChambers[CurrentBulletIndex] == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Loading bullet"))
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Loading bullet"));
		BulletChambers[CurrentBulletIndex] = true;
		if (CurrentBulletIndex < 0)
		{
			CurrentBulletIndex = 5;
		}
		else if (CurrentBulletIndex > 5)
		{
			CurrentBulletIndex = 0;
		}
		UE_LOG(LogTemp, Warning, TEXT("CurrentCylinder = %d"), CurrentBulletIndex)
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet Already In the Chamber!"))
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Bullet Already In the Chamber!"));
	}
}

void ATHNPlayerCharacter::HandleCycleCylinderLeftInput(const FInputActionValue& InputActionValue)
{
	//The scrolling will probably need to be adjusted/changed in the future
	//It's too easy to over and underscroll
	//UE_LOG(LogTemp, Warning, TEXT("Cycling cylinder left"))
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Cycling cylinder left"));
	CurrentBulletIndex++;
	if (CurrentBulletIndex == 6)
	{
		CurrentBulletIndex = 0;
	}
	UE_LOG(LogTemp, Warning, TEXT("CurrentCylinder = %d"), CurrentBulletIndex)
	RotateCylinderCounterClockwise();
}

void ATHNPlayerCharacter::HandleCycleCylinderRightInput(const FInputActionValue& InputActionValue)
{
	//The scrolling will probably need to be adjusted/changed in the future
	//It's too easy to over and underscroll
	//UE_LOG(LogTemp, Warning, TEXT("Cycling cylinder right"))
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Cycling cylinder right"));
	CurrentBulletIndex--;
	if (CurrentBulletIndex == -1)
	{
		CurrentBulletIndex = 5;
	}
	UE_LOG(LogTemp, Warning, TEXT("CurrentCylinder = %d"), CurrentBulletIndex)
	RotateCylinderClockwise();
}

void ATHNPlayerCharacter::HandleChangeColorRedInput(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Warning, TEXT("RED %s"), *this->GetName());
	CurrentIncubatorColor = EIncubatorPuzzleColor::Red;
}

void ATHNPlayerCharacter::HandleChangeColorGreenInput(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Warning, TEXT("GREEN"));
	CurrentIncubatorColor = EIncubatorPuzzleColor::Green;
}

void ATHNPlayerCharacter::HandleChangeColorBlueInput(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Warning, TEXT("BLUE"));
	CurrentIncubatorColor = EIncubatorPuzzleColor::Blue;
}

void ATHNPlayerCharacter::HandlePuzzleRotateHorizontalStartInput(const FInputActionValue& InputActionValue)
{
	IsRotatingPuzzle = true;
	RotateInputVector = FVector2D(InputActionValue.Get<FVector2D>().X, RotateInputVector.Y);
	UE_LOG(LogTemp, Warning, TEXT("Horizontal: %f, %f"), RotateInputVector.X, RotateInputVector.Y);
}

void ATHNPlayerCharacter::HandlePuzzleRotateHorizontalEndInput(const FInputActionValue& InputActionValue)
{
	IsRotatingPuzzle = false;
	RotateInputVector = FVector2D(0, RotateInputVector.Y);
	UE_LOG(LogTemp, Warning, TEXT("Horizontal: %f, %f"), RotateInputVector.X, RotateInputVector.Y);
}

void ATHNPlayerCharacter::HandlePuzzleRotateVerticalStartInput(const FInputActionValue& InputActionValue)
{
	IsRotatingPuzzle = true;
	RotateInputVector = FVector2D(RotateInputVector.X, InputActionValue.Get<FVector2D>().X);
	UE_LOG(LogTemp, Warning, TEXT("Vertical: %f, %f"), RotateInputVector.X, RotateInputVector.Y);
}

void ATHNPlayerCharacter::HandlePuzzleRotateVerticalEndInput(const FInputActionValue& InputActionValue)
{
	IsRotatingPuzzle = false;
	RotateInputVector = FVector2D(RotateInputVector.X, 0);
	UE_LOG(LogTemp, Warning, TEXT("Vertical: %f, %f"), RotateInputVector.X, RotateInputVector.Y);
}

void ATHNPlayerCharacter::HandleClickInput(const FInputActionValue& InputActionValue)
{
	//TODO: Store a reference to the puzzles in the game instance to retrieve easier
	TArray<AActor*> DataPoisoningPuzzles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATHNDataPoisoningPuzzle::StaticClass(), DataPoisoningPuzzles);
	Cast<ATHNDataPoisoningPuzzle>(DataPoisoningPuzzles[0])->OnClickDelegate.Broadcast(CurrentInteractActor);
}
