// Fill out your copyright notice in the Description page of Project Settings.


#include "SubmergePlayerController.h"
#include "SubmergePlayerCharacter.h"

void ASubmergePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASubmergePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
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
}

void ASubmergePlayerController::CallMoveForward(float Value)
{
	PossessedCharacter->MoveForward(Value);
	// this is the same character from begin play
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


// inside the tick get pawn and also leave in begin play
