// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SubmergeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SUBMERGE_API USubmergeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	virtual void OnStart() override;
	
};
