// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LiftMovementComponent.generated.h"

class USphereComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBMERGE_API ULiftMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULiftMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//DECLARE_EVENT(ULiftMovementComponent, FReachedNewLevel)
	//	FReachedNewLevel& NewLevelReached() { return ReachedNewLevel; }

	void MoveLift();
	void IncrementCounter() { CurrentLevel++; }

	bool GetActiveState() { return LiftActivated; }
	void SetActiveState(bool State) { LiftActivated = State; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TObjectPtr<APawn> PlayerCharacter;
	TObjectPtr<USphereComponent> OwnerSphereComponent;

	bool LiftActivated = false;

	unsigned int CurrentLevel = 0;

	FVector StartLocation = FVector::ZeroVector;
	FVector NextLocation = FVector::ZeroVector;

	float CurrentMovementTime = 0.f;

	UPROPERTY(EditAnywhere, Category = "Levels")
		float TimeToMove = 5.f;

	UPROPERTY(EditAnywhere, Category = "Levels")
		unsigned int NumberOfLevels = 4;

	UPROPERTY(EditAnywhere, Category = "Levels")
		TArray<float> Levels;

	UPROPERTY(EditAnywhere, Category = "Levels")
		FRuntimeFloatCurve MovementCurve;

	//FReachedNewLevel ReachedNewLevel;

	void UpdateLevelAndLocation();
};
