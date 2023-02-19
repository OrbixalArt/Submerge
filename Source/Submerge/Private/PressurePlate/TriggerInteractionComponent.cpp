// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate/TriggerInteractionComponent.h"
#include "Components/BoxComponent.h"
#include "PressurePlate/ActorMovementComponent.h"

// Sets default values
UTriggerInteractionComponent::UTriggerInteractionComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

	ActorMoveComp = CreateDefaultSubobject<UActorMovementComponent>(FName("ActorMoveComp"));
}

// Called when the game starts or when spawned
void UTriggerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	Box = GetOwner()->FindComponentByClass<UBoxComponent>();
	
	if(Box)
	{
		Box->OnComponentBeginOverlap.AddDynamic(this, &UTriggerInteractionComponent::OnOverlapBegin);
		Box->OnComponentEndOverlap.AddDynamic(this, &UTriggerInteractionComponent::OnOverlapEnd);
	}

}

void UTriggerInteractionComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Overlap = true;

}

void UTriggerInteractionComponent::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Overlap = false;

}

void UTriggerInteractionComponent::ActivateTrigger()
{
	if (Overlap)
	{
		ActorMoveComp->Move();
		OnActivation().Broadcast();
	}
}

void UTriggerInteractionComponent::DeactivateTrigger()
{
	if (!Overlap)
	{
		ActorMoveComp->MoveBack();
		OnDeactivation().Broadcast();
	}
}

// called every frame
void UTriggerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ActivateTrigger();
	DeactivateTrigger();
}



