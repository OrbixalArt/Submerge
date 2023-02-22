// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveableObject.h"

// Sets default values
AMoveableObject::AMoveableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMoveableObject::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalLocation = GetActorLocation();
	OriginalRotation = GetActorRotation();
}

