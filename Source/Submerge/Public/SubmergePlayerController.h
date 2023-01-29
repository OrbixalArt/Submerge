// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SubmergePlayerController.generated.h"

/**
 * 
 */

class ASubmergePlayerCharacter;

UCLASS()
class SUBMERGE_API ASubmergePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
		void CallMoveForward(float Value);

	UFUNCTION(BlueprintCallable)
		void CallMoveRight(float Value);

	UFUNCTION(BlueprintCallable)
		void CallLookUp(float Value);

	UFUNCTION(BlueprintCallable)
		void CallLookRight(float Value);

	UFUNCTION(BlueprintCallable)
		void CallGrab();

	UFUNCTION(BlueprintCallable)
		void CallRelease();

	//UFUNCTION(BlueprintCallable)
	//void CallInteract();

	ASubmergePlayerCharacter* PossessedCharacter;

};
