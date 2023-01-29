// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SubmergePlayerCharacter.generated.h"

class UCameraComponent;
class UGrabComponent;
class UPhysicsHandleComponent;

UCLASS()
class SUBMERGE_API ASubmergePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASubmergePlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Movement Speed")
		float HoldSpeed = 0.7f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
		UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(VisibleAnywhere)
		UGrabComponent* Grabber;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Grab();
	void Release();


};
