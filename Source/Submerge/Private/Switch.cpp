// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/Soundbase.h"
#include "Sound/SoundNodeSwitch.h"

// Sets default values
ASwitch::ASwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASwitch::TurnOn()
{
	if (SwitchState == ESwitchState::E_Off)
	{
		SwitchState = ESwitchState::E_On;
		LiftSwitchedOn.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("Switch is turned on."));
		// Broadcast event to lift
		UGameplayStatics::SpawnSoundAtLocation(this, SwitchSound, GetActorLocation());
	}
}



