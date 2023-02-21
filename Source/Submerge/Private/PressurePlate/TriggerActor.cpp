// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate/TriggerActor.h"
#include "Components/BoxComponent.h"
#include "PressurePlate/TriggerInteractionComponent.h"

// Sets default values
ATriggerActor::ATriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("BoxComp"));
	RootComponent = BoxComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	TriggerInteractionComponent = CreateDefaultSubobject<UTriggerInteractionComponent>(FName("TriggerInteractionComponent"));
}




