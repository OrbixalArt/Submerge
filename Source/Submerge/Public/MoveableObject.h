// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveableObject.generated.h"

UCLASS()
class SUBMERGE_API AMoveableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveableObject();

	UFUNCTION(BlueprintCallable)
	void ResetPosition() { SetActorLocationAndRotation(OriginalLocation, OriginalRotation); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector OriginalLocation = FVector::ZeroVector;
	FRotator OriginalRotation = FRotator::ZeroRotator;

};
