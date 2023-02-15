// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lift.generated.h"

class ULiftMovementComponent;
class USphereComponent;

UCLASS()
class SUBMERGE_API ALift : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALift();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ActivateLift();

	// TriggerBox to activate lift and check if player is in bounds
	// Make TriggerBox smaller than the lift space

	// Lift Movement Component (Net Movement)
	// - need a counter to keep track of which floor the player is on.

	// Lift Doors have a separate movement component



	/* Lift (without button) Steps:
		1: Doors down (player does level)
		2: Player uses the switch -> Lift is active
		3: Player walks into lift -> Doors rise -> Lift moves
		4: Lift reaches next level -> Lift is inactive -> Doors down */

	UPROPERTY(EditAnywhere)
	TObjectPtr<ULiftMovementComponent> LiftMovementComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> Sphere;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
