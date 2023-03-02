// Fill out your copyright notice in the Description page of Project Settings.


#include "Lift.h"
#include "Switch.h"
#include "LiftMovementComponent.h"
#include "LiftDoorComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALift::ALift()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	RootComponent = Sphere;

	LiftMovementComponent = CreateDefaultSubobject<ULiftMovementComponent>(FName("LiftMovementComponent"));
	LiftDoorComponent = CreateDefaultSubobject<ULiftDoorComponent>(FName("LiftDoorComponent"));


}

int ALift::GetCurrentGameLevel()
{
	return LiftMovementComponent->GetCurrentLevel();
}

int ALift::GetNumberOfLevels()
{
	return LiftMovementComponent->GetNumberOfLevels();
}

// Called when the game starts or when spawned
void ALift::BeginPlay()
{
	Super::BeginPlay();

	// TArray<TObjectPtr<AActor>> SwitchesInGame;
	// UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASwitch::StaticClass(), SwitchesInGame);

	for (int i = 0; i < SwitchesInGame.Num();i++)
	{
		TObjectPtr<ASwitch> Switch = Cast<ASwitch>(SwitchesInGame[i]);
		if(IsValid(Switch))
		{
			Switch->LiftSwitchedOn.AddDynamic(this, &ALift::ActivateLift);
			UKismetSystemLibrary::PrintString(GetWorld(), FString("This is binding"), true, false, FLinearColor::Red, 4.f);
			UE_LOG(LogTemp, Error, TEXT("Switch binding."));
		}
	}	
}

void ALift::ActivateLift()
{
	if (!LiftMovementComponent->GetActiveState())
	{
		// LiftMovementComponent->SetActiveState(true);
		LiftDoorComponent->SetDoorsActive(true);
		LiftDoorComponent->ResetCounter();
		LiftMovementComponent->SetNewLevel(true);
		UE_LOG(LogTemp, Error, TEXT("Lift is on"));
	}

}

