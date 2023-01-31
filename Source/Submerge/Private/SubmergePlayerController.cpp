// Fill out your copyright notice in the Description page of Project Settings.


#include "SubmergePlayerController.h"
#include "SubmergePlayerCharacter.h"

void ASubmergePlayerController::BeginPlay()
{
	Super::BeginPlay();

	PossessedCharacter = Cast<ASubmergePlayerCharacter>(GetPawn());
}

void ASubmergePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(FName("MoveForward"), this, &ASubmergePlayerController::CallMoveForward);
	InputComponent->BindAxis(FName("MoveRight"), this, &ASubmergePlayerController::CallMoveRight);
	InputComponent->BindAxis(FName("LookUp"), this, &ASubmergePlayerController::CallLookUp);
	InputComponent->BindAxis(FName("LookRight"), this, &ASubmergePlayerController::CallLookRight);

	InputComponent->BindAction(FName("Interact"), IE_Pressed, this, &ASubmergePlayerController::CallGrab);
	InputComponent->BindAction(FName("Interact"), IE_Released, this, &ASubmergePlayerController::CallRelease);
}

void ASubmergePlayerController::CallMoveForward(float Value)
{
	PossessedCharacter->MoveForward(Value);
}

void ASubmergePlayerController::CallMoveRight(float Value)
{
	PossessedCharacter->MoveRight(Value);
}

void ASubmergePlayerController::CallLookUp(float Value)
{
	AddPitchInput(Value);
}

void ASubmergePlayerController::CallLookRight(float Value)
{
	AddYawInput(Value);
}

void ASubmergePlayerController::CallGrab()
{
	PossessedCharacter->Grab();
}

void ASubmergePlayerController::CallRelease()
{
	PossessedCharacter->Release();
}
