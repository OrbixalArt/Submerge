// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TriggerReactComponent.generated.h"

class ATriggerActor;
class UTriggerInteractionComponent;
class UActorMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBMERGE_API UTriggerReactComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerReactComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TObjectPtr<UActorMovementComponent> ReactActorMoveComp;

	bool MoveState = false;

	UFUNCTION()
		void ActivateActor();

	UFUNCTION()
		void DeactivateActor();

	TObjectPtr<UTriggerInteractionComponent> TriggerCompEventSource;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		TObjectPtr<ATriggerActor> TriggerActorEventSource;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UActorMovementComponent> ActorMoveComponent;
};
