// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UGrabComponent::UGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get Capsule
	Capsule = GetOwner()->FindComponentByClass<UCapsuleComponent>();
	if (Capsule)
	{
		// Do nothing
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Capsule found"));
	}

	// Get Camera
	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
	if (Camera)
	{
		// Do nothing
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Camera found"));
	}

	// Get Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Do nothing
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle found"));
	}

}

// Called every frame
void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (HoldingObject)
	{
		if (Capsule)
		{
			FVector Start = Capsule->GetComponentLocation();
			FVector End = (Capsule->GetComponentRotation().Vector() * HoldDistance) + Start;

			End.Z += HoldHeight;

			if (PhysicsHandle->GrabbedComponent)
			{
				PhysicsHandle->SetTargetLocation(End);
			}
		}
	}

}

void UGrabComponent::Grab()
{
	if (HoldingObject)
	{
		PhysicsHandle->GrabbedComponent->SetCollisionProfileName(FName("PhysicsActor"));
		PhysicsHandle->ReleaseComponent();
		HoldingObject = false;
	}
	else
	{
		if (Camera)
		{
			PickUpObject();
		}
	}
}

void UGrabComponent::PickUpObject()
{
	// Setup for linetrace
	FVector Start = Camera->GetComponentLocation();
	FVector End = (Camera->GetComponentRotation().Vector() * InteractionDistance) + Start;
	FCollisionQueryParams CollisionParams(FName(TEXT("")), false, GetOwner());

	// Check for pickup objects
	FHitResult HitResult;
	bool IsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End,
		ECC_PhysicsBody, CollisionParams);

	// Check for objects in front of pickup objects
	FHitResult ObstacleHit;
	bool ObHit = GetWorld()->LineTraceSingleByObjectType(ObstacleHit, Start, End,
		ECC_WorldStatic, CollisionParams);

	
	// Check for obstructing objects
	if (!ObHit)
	{
		// Check for pickup object hit
		if (IsHit)
		{
			CheckIfObjectIsBelow(HitResult, Start, End);
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.f);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Raycast obstructed"));
	}
}

// No longer checks if there is an object below
void UGrabComponent::CheckIfObjectIsBelow(const FHitResult& HitResult, const FVector& Start, const FVector& End)
{
	AActor* Actor = HitResult.GetActor();
	UE_LOG(LogTemp, Error, TEXT("Raycast hit: %s"), *FString(Actor->GetName()));
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.f);

	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	if (ComponentToGrab && (ComponentToGrab != CollideComp))
	{
		ComponentToGrab->AddImpulse(FVector(0.f, 0.f, 0.1f), FName("NAME_None"), true);

		//Actor->SetActorEnableCollision(false);
		ComponentToGrab->SetCollisionProfileName(FName("PickedUp"));

		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, FName("NAME_None"), HitResult.Location, ComponentToGrab->GetComponentRotation());

		HoldingObject = true;
	}
}

// Not relevant atm
TArray<FHitResult> UGrabComponent::CheckCollisionUnderneath() const
{
	TArray<FHitResult> HitResult;

	// Check right underneath the capsule
	FCollisionQueryParams CollisionParams(FName(TEXT("")), false, GetOwner());


	for (size_t i = 0; i < Iterations; i++)
	{
		FVector Start = Capsule->GetComponentLocation();
		Start += Capsule->GetForwardVector() * (i/(Iterations-1)) * (Capsule->GetScaledCapsuleRadius() + 20);
		FVector End = (Capsule->GetUpVector()) + Start;
		End.Z *= -1;
		FHitResult Result;
		bool Hit = GetWorld()->LineTraceSingleByObjectType(Result, Start, End,
			ECC_PhysicsBody, CollisionParams);

		HitResult.Emplace(Result);

		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.f);
	}

	return HitResult;
}

