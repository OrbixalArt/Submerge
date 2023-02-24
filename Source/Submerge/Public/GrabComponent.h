// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabComponent.generated.h"

class UPhysicsHandleComponent;
class UCapsuleComponent;
class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBMERGE_API UGrabComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly)
	class UInteractWidget* InteractWidget;

	TObjectPtr<UPhysicsHandleComponent> PhysicsHandle = nullptr;
	TObjectPtr<UCapsuleComponent> Capsule = nullptr;
	TObjectPtr<UCameraComponent> Camera = nullptr;

	TObjectPtr<UPrimitiveComponent> CollideComp;

	UPROPERTY(EditAnywhere, Category = "Reach")
		float InteractionDistance = 200.f;

	UPROPERTY(EditAnywhere, Category = "Reach")
		float HoldDistance = 120.f;

	UPROPERTY(EditAnywhere, Category = "Reach")
		float HoldHeight = 40.f;

	size_t Iterations = 2;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Grab();

	bool HoldingObject = false;

protected:
	void PickUpObject();
	void CheckIfObjectIsBelow(const FHitResult& HitResult, const FVector& Start, const FVector& End);
	TArray<FHitResult> CheckCollisionUnderneath() const;

	UPROPERTY(EditAnywhere)
	class USoundBase* PickUpSound;
	UPROPERTY(EditAnywhere)
    class USoundBase* PutDownSound;
};
