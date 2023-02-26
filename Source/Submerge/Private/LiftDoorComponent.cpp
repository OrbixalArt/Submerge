// Fill out your copyright notice in the Description page of Project Settings.


#include "LiftDoorComponent.h"
#include "LiftDoor.h"
#include "LiftMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/Soundbase.h"


// Sets default values for this component's properties
ULiftDoorComponent::ULiftDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void ULiftDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	if(LiftDoors)
	{
		LiftDoors->SetActorLocation(GetOwner()->GetActorLocation());
		LiftDoors->SetActorRotation(GetOwner()->GetActorRotation());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("LiftDoorComponent does not have a Lift Doors Object selected."));
	}

	LiftMoveComp = GetOwner()->FindComponentByClass<ULiftMovementComponent>();
	if (LiftMoveComp)
	{
		LiftMoveComp->NewLevelReached().AddUObject(this, &ULiftDoorComponent::NewLevel);
	}
}

void ULiftDoorComponent::MoveDoors()
{
	if ((CurrentMovementTime < TimeToMove))
	{
		if (CurrentMovementTime <= 0)
		{
			UGameplayStatics::SpawnSoundAtLocation(this, LiftDoorSound, GetOwner()->GetActorLocation());
		}

		UE_LOG(LogTemp, Error, TEXT("MoveDoor Branch: %f"), CurrentMovementTime);
		CurrentMovementTime = FMath::Clamp(CurrentMovementTime + GetWorld()->DeltaTimeSeconds, 0.0f, TimeToMove);
		CurrentNegationTime = FMath::Clamp(CurrentNegationTime - GetWorld()->DeltaTimeSeconds, 0.0f, TimeToMove);

		const float TimeRatio = FMath::Clamp(CurrentMovementTime / TimeToMove, 0.0f, 1.0f);
		const float MovementAlpha = MovementCurve.GetRichCurveConst()->Eval(TimeRatio);
		const FVector CurrentLocation = FMath::Lerp(StartLocation, NextLocation, MovementAlpha);
		

		if (LiftDoors)
		{
			LiftDoors->SetActorLocation(CurrentLocation);
		}
	}
}

void ULiftDoorComponent::MoveDoorsBack()
{
	if (CurrentMovementTime > 0.f)
	{
		if (CurrentMovementTime >= 1)
		{
			UGameplayStatics::SpawnSoundAtLocation(this, LiftDoorSound, GetOwner()->GetActorLocation());
		}

		UE_LOG(LogTemp, Error, TEXT("MoveDoorBack Branch: %f"), CurrentMovementTime);
		CurrentMovementTime = FMath::Clamp(CurrentMovementTime - GetWorld()->DeltaTimeSeconds, 0.0f, TimeToMove);
		CurrentNegationTime = FMath::Clamp(CurrentNegationTime + GetWorld()->DeltaTimeSeconds, 0.0f, TimeToMove);

		const float TimeRatio = FMath::Clamp(CurrentNegationTime / TimeToMove, 0.0f, 1.0f);
		const float MovementAlpha = MovementCurve.GetRichCurveConst()->Eval(TimeRatio);
		const FVector CurrentLocation = FMath::Lerp(NextLocation, StartLocation, MovementAlpha);

		if (LiftDoors)
		{
			LiftDoors->SetActorLocation(CurrentLocation);
		}

		if (CurrentNegationTime == TimeToMove)
		{
			if (DoorsActivationCounter < 1)
			{
				ActivateLift().Broadcast();
				DoorsActivationCounter++;
			}
		}
	}
}


void ULiftDoorComponent::NewLevel()
{
	SetLiftMoving(false);
	SetDoorsActive(true);
	UE_LOG(LogTemp, Error, TEXT("New Level Reached"));
}

// Called every frame
void ULiftDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (LiftIsMoving)
	{
		if (LiftDoors)
		{
			LiftDoors->SetActorLocation(GetOwner()->GetActorLocation());
		}
	}
	else
	{
		if (StartLocation != GetOwner()->GetActorLocation())
		{
			StartLocation = GetOwner()->GetActorLocation();
			NextLocation = StartLocation;
			NextLocation.Z += DoorTravelDistance;
		}

		if (DoorsActivated)
		{
			MoveDoors();
		}
		else
		{
			MoveDoorsBack();
		}
	}
}

