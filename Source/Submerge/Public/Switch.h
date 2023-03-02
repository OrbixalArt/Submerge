// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Switch.generated.h"


UENUM(BlueprintType)
enum class ESwitchState : uint8 {
	E_On	UMETA(DisplayName = "On"),
	E_Off	UMETA(DisplayName = "Off"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLiftSwitchedOn);

UCLASS()
class SUBMERGE_API ASwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwitch();

	UPROPERTY(BlueprintAssignable)
		FLiftSwitchedOn LiftSwitchedOn;

	UFUNCTION(BlueprintCallable)
	void TurnOn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	ESwitchState SwitchState = ESwitchState::E_Off;

	UPROPERTY(EditAnywhere)
	class USoundBase* SwitchSound;
};
