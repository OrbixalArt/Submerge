// Fill out your copyright notice in the Description page of Project Settings.


#include "ReactActor.h"
#include "TriggerReactComponent.h"

// Sets default values
AReactActor::AReactActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	RootComponent = Mesh;

	TriggerReactComp = CreateDefaultSubobject<UTriggerReactComponent>(FName("TriggerReactComp"));
}

