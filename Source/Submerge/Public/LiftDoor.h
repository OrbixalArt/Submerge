// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LiftDoor.generated.h"

UCLASS()
class SUBMERGE_API ALiftDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALiftDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
