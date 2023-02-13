// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBMERGE_API UActorMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool State = false;

	UPROPERTY(EditAnywhere, Category = "Trigger Movement")
		FRuntimeFloatCurve MovementCurve;

	UPROPERTY(EditAnywhere, Category = "Trigger Movement")
		FVector NetMovement = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Trigger Movement")
		float TimeToMove = 1.f;

	float CurrentMovementTime = 0.f;
	float NegationMovementTime = TimeToMove;

	FVector StartLocation = FVector::ZeroVector;
	FVector FinalLocation = FVector::ZeroVector;

public:	
	UFUNCTION(BlueprintCallable)
	bool GetState() { return State; }

	UFUNCTION(BlueprintCallable)
	void Move();

	UFUNCTION(BlueprintCallable)
	void MoveBack();
};
