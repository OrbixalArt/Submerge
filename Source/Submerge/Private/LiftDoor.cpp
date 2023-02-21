// Fill out your copyright notice in the Description page of Project Settings.


#include "LiftDoor.h"

// Sets default values
ALiftDoor::ALiftDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));

}

// Called when the game starts or when spawned
void ALiftDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

