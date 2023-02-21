// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerActor.generated.h"

class UBoxComponent;
class UTriggerInteractionComponent;

UCLASS()
class SUBMERGE_API ATriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerActor();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTriggerInteractionComponent> TriggerInteractionComponent;

};
