#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "THNPossessableActorComponent.generated.h"

class UTHNAnimInstance;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTHNPossessableActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:    
	// Sets default values for this component's properties
	UTHNPossessableActorComponent();
	void AttachDroneToSocket();

	///<summary>Selects and sets random possession spots to be active. The amount of spots that are activated depends on NumActiveDronesInBody</summary>
	UFUNCTION(CallInEditor, BlueprintCallable, Category="Tools")
	void RandomizePossessionPosition();

	UFUNCTION(CallInEditor, Category="Tools")
	void ClearPossessionPositions();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone")
	bool bDoesDroneExist;

	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Drone")
	bool DoesDroneExist();

private:

	UPROPERTY()
	UTHNAnimInstance* OwnerAnimInstance;

	UPROPERTY()
	UTHNAnimInstance* OwnerProbeAnimInstance;

	UPROPERTY(EditAnywhere, Category="Tools")
	FName PossessionSocketName = "PossessionLocation";

	UPROPERTY(EditAnywhere, Category="Tools")
	float PossessionSpotDebugSize = 5;

	//Just in case we want multiple drone spots within a single enemy
	UPROPERTY(EditAnywhere, Category="Possession Settings")
	uint16 NumActiveDronesInBody = 1;

	//All of the possible possession spots on the skeletal mesh
	TArray<TObjectPtr<USkeletalMeshSocket>> PossessionSockets;

	//The spot that is currently being used by a drone
	TArray<TObjectPtr<USkeletalMeshSocket>> ActivePossessionSockets;

	UPROPERTY()
	USkeletalMeshComponent* InvisMesh;

	///<summary> Gets all sockets matching PossessionSocketName and caches them </summary>
	void InitializePossessionSockets();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> DebugDroneBlueprint;

	UPROPERTY()
	TArray<AActor*> DebugDrones;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:    
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};