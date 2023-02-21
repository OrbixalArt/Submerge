// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate/ActorMovementComponent.h"

// Sets default values for this component's properties
UActorMovementComponent::UActorMovementComponent()
{

}


// Called when the game starts
void UActorMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	FinalLocation = GetOwner()->GetActorLocation() + NetMovement;
	
}

void UActorMovementComponent::Move()
{
	if (CurrentMovementTime != TimeToMove)
	{
		CurrentMovementTime = FMath::Clamp(CurrentMovementTime + GetWorld()->DeltaTimeSeconds, 0.0f, TimeToMove);

		NegationMovementTime = FMath::Clamp(NegationMovementTime - GetWorld()->DeltaTimeSeconds, 0.0f, TimeToMove);

		const float TimeRatio = FMath::Clamp(CurrentMovementTime / TimeToMove, 0.0f, 1.0f);
		const float MovementAlpha = MovementCurve.GetRichCurveConst()->Eval(TimeRatio);
		const FVector CurrentLocation = FMath::Lerp(StartLocation, FinalLocation, MovementAlpha);
		GetOwner()->SetActorLocation(CurrentLocation);

		if (CurrentLocation == FinalLocation)
		{
			State = true;
		}
	}
}

void UActorMovementComponent::MoveBack()
{
	if (CurrentMovementTime != 0.f)
	{
		CurrentMovementTime = FMath::Clamp(CurrentMovementTime - GetWorld()->DeltaTimeSeconds, 0.0f, TimeToMove);

		NegationMovementTime = FMath::Clamp(NegationMovementTime + GetWorld()->DeltaTimeSeconds, 0.0f, TimeToMove);

		const float TimeRatio = FMath::Clamp(NegationMovementTime / TimeToMove, 0.0f, 1.0f);
		const float MovementAlpha = MovementCurve.GetRichCurveConst()->Eval(TimeRatio);
		const FVector CurrentLocation = FMath::Lerp(FinalLocation, StartLocation, MovementAlpha);
		GetOwner()->SetActorLocation(CurrentLocation);

		if (CurrentLocation == StartLocation)
		{
			State = false;
		}
	}
}

