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

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Physics Handle is found
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

	// ...

	//UCameraComponent* Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
	UCapsuleComponent* Capsule = GetOwner()->FindComponentByClass<UCapsuleComponent>();

	if (Capsule)
	{
		FVector Start = Capsule->GetComponentLocation();
		FVector End = (Capsule->GetComponentRotation().Vector() * HoldDistance) + Start;

		End.Z += HoldHeight;

		if (PhysicsHandle->GrabbedComponent)
		{
			PhysicsHandle->SetTargetLocation(End);

			//UPrimitiveComponent* GrabbedComp = PhysicsHandle->GetGrabbedComponent();
			//
			//GrabbedComp->SetWorldRotation(GetOwner()->GetActorRotation());
		}
	}

}

void UGrabComponent::Grab()
{

	UCameraComponent* Camera = GetOwner()->FindComponentByClass<UCameraComponent>();

	if (Camera)
	{
		FVector Start = Camera->GetComponentLocation();
		FVector End = (Camera->GetComponentRotation().Vector() * InteractionDistance) + Start;
		FHitResult HitResult;

		//TArray<AActor*> ActorsToIgnore;

		FCollisionQueryParams CollisionParams(FName(TEXT("")), false, GetOwner());


		bool IsHit = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End,
			ECC_PhysicsBody, CollisionParams);

		FHitResult ObstacleHit;

		bool ObHit = GetWorld()->LineTraceSingleByObjectType(ObstacleHit, Start, End,
			ECC_WorldStatic, CollisionParams);


		UE_LOG(LogTemp, Error, TEXT("%s"), (IsHit ? TEXT("true") : TEXT("false")));

		// Need to simplify this list of nested if statements by creating more functions
		// This will be done soon
		
		if (!ObHit)
		{
			if (IsHit)
			{
				AActor* Actor = HitResult.GetActor();
				UE_LOG(LogTemp, Error, TEXT("Raycast hit: %s"), *FString(Actor->GetName()));
				DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.f);


				UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

				if (ComponentToGrab)
				{
					ComponentToGrab->AddImpulse(FVector(0.f, 0.f, 0.1f), FName("NAME_None"), true);

					//PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, FName("NAME_None"), HitResult.ImpactPoint);

					PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, FName("NAME_None"), HitResult.Location, ComponentToGrab->GetComponentRotation());

					//HitResult.ImpactPoint
					HoldingObject = true;
				}
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
}

void UGrabComponent::Release()
{
	if (HoldingObject)
	{
		PhysicsHandle->ReleaseComponent();
		HoldingObject = false;
	}
}
