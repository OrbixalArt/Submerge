// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate/ReactActor.h"
#include "PressurePlate/TriggerReactComponent.h"

// Sets default values
AReactActor::AReactActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	RootComponent = Mesh;

	TriggerReactComp = CreateDefaultSubobject<UTriggerReactComponent>(FName("TriggerReactComp"));
}

