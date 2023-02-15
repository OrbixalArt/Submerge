// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TriggerInteractionComponent.generated.h"

class UBoxComponent;
class UActorMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBMERGE_API UTriggerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerInteractionComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// declare overlap begin function
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool Overlap = false;

	void ActivateTrigger();
	void DeactivateTrigger();

public:

	DECLARE_EVENT(UTriggerInteractionComponent, FActivated)
		FActivated& OnActivation() { return Activated; }

	DECLARE_EVENT(UTriggerInteractionComponent, FDeactivated)
		FDeactivated& OnDeactivation() { return Deactivated; }

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UActorMovementComponent> ActorMoveComp;

protected:
	// events

	FActivated Activated;

	FDeactivated Deactivated;

};
