// Fill out your copyright notice in the Description page of Project Settings.


#include "Lift.h"
#include "Switch.h"

// Sets default values
ALift::ALift()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALift::BeginPlay()
{
	Super::BeginPlay();

	//Switch->OnActivation().AddUObject(this, &ALift::ActivateLift);
	
}

void ALift::ActivateLift()
{
	if (!LiftActivated)
	{
		LiftActivated = true;
		// increase the counter on the Lift Movement Component
	}
}

// Called every frame
void ALift::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

