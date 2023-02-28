// Fill out your copyright notice in the Description page of Project Settings.


#include "LiftMovementComponent.h"
#include "LiftDoorComponent.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
ULiftMovementComponent::ULiftMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULiftMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
	OwnerSphereComponent = GetOwner()->FindComponentByClass<USphereComponent>();
	LiftDoors = GetOwner()->FindComponentByClass<ULiftDoorComponent>();

	if (LiftDoors)
	{
		LiftDoors->ActivateLift().AddUObject(this, &ULiftMovementComponent::ActivateLift);
	}

	StartLocation = GetOwner()->GetActorLocation();
	NextLocation = StartLocation + FVector(0.f, 0.f, Levels[1]);
	
}

void ULiftMovementComponent::ActivateLift()
{
	SetActiveState(true);
	UE_LOG(LogTemp, Warning, TEXT("Lift is activated via event"));
}

void ULiftMovementComponent::UpdateLevelAndLocation()
{
	if (CurrentMovementTime == TimeToMove)
	{
		if (CurrentLevel < (NumberOfLevels - 2))
		{
			IncrementCounter();
			CurrentMovementTime = 0.f;
			StartLocation = NextLocation;
			NextLocation = StartLocation + FVector(0.f, 0.f, Levels[CurrentLevel + 1]);
		}
		else
		{
			IncrementCounter();
		}

		SetActiveState(false);
		LiftDoors->SetLiftMoving(false);
		UE_LOG(LogTemp, Error, TEXT("Lift is off"));
		NewLevelReached().Broadcast();
	}

}


// Called every frame
void ULiftMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveLift();
}

void ULiftMovementComponent::MoveLift()
{
	if (LiftActivated)
	{
		LiftDoors->SetLiftMoving(true);
		if (!PlayerCharacter)
		{
			PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
		}

		if ((CurrentMovementTime != TimeToMove) && OwnerSphereComponent->IsOverlappingActor(PlayerCharacter))
		{
			CurrentMovementTime = FMath::Clamp(CurrentMovementTime + GetWorld()->DeltaTimeSeconds, 0.0f, TimeToMove);

			const float TimeRatio = FMath::Clamp(CurrentMovementTime / TimeToMove, 0.0f, 1.0f);
			const float MovementAlpha = MovementCurve.GetRichCurveConst()->Eval(TimeRatio);
			const FVector CurrentLocation = FMath::Lerp(StartLocation, NextLocation, MovementAlpha);
			GetOwner()->SetActorLocation(CurrentLocation);

			UpdateLevelAndLocation();
		}
	}
	else
	{
		if (!PlayerCharacter)
		{
			PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
		}

		if (PlayerCharacter)
		{
			if (OwnerSphereComponent->IsOverlappingActor(PlayerCharacter) && NewLevel)
			{
				LiftDoors->SetDoorsActive(false);
				SetNewLevel(false);
			}
		}
	}
}

