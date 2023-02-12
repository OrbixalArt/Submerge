// Fill out your copyright notice in the Description page of Project Settings.


#include "SubmergePlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "GrabComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values
ASubmergePlayerCharacter::ASubmergePlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(RootComponent);

	Grabber = CreateDefaultSubobject<UGrabComponent>(FName("Grabber"));

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(FName("PhysicsHandle"));
}

// Called when the game starts or when spawned
void ASubmergePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASubmergePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASubmergePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASubmergePlayerCharacter::MoveForward(float Value)
{

	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), !Grabber->HoldingObject ? Value : Value * HoldSpeed);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("false"));
}

void ASubmergePlayerCharacter::MoveRight(float Value)
{
	if (Controller)
	{
		AddMovementInput(GetActorRightVector(), !Grabber->HoldingObject ? Value : Value * HoldSpeed);
	}
}

void ASubmergePlayerCharacter::Grab()
{
	if (Controller)
	{
		Grabber->Grab();
	}
}
