// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LiftDoorComponent.generated.h"

class ALiftDoor;
class ULiftMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBMERGE_API ULiftDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULiftDoorComponent();

	DECLARE_EVENT(ULiftDoorComponent, FActivateLift)
		FActivateLift& ActivateLift() { return ActiveLift; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void MoveDoors();
	void MoveDoorsBack();

	void LiftIsMovingActivate() { LiftIsMoving = true; }

	FActivateLift ActiveLift;

	UPROPERTY(EditAnywhere, Category = "Doors")
		float DoorTravelDistance = 0.f;

	FVector StartLocation = FVector::ZeroVector;
	FVector NextLocation = FVector::ZeroVector;

	float CurrentMovementTime = 0.f;
	float CurrentNegationTime = TimeToMove;

	UPROPERTY(EditAnywhere, Category = "Doors")
		float TimeToMove = 1.f;

	UPROPERTY(EditAnywhere, Category = "Doors")
		FRuntimeFloatCurve MovementCurve;

	bool DoorsActivated = false;

	bool LiftIsMoving = false;

	int DoorsActivationCounter = 0;

	UPROPERTY(EditAnywhere, Category = "Doors")
		TObjectPtr<ALiftDoor> LiftDoors;

	TObjectPtr<ULiftMovementComponent> LiftMoveComp;

	void NewLevel();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetDoorsActive(bool State) { DoorsActivated = State; }
	bool GetDoorsActive() { return DoorsActivated; }

	void SetLiftMoving(bool State) { LiftIsMoving = State; }
	bool GetLiftMoving() { return LiftIsMoving; }

	void ResetCounter() { DoorsActivationCounter = 0; }
};
