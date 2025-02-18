// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementBaseState.h"
#include "UObject/Object.h"
#include "WalkForwardState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UWalkForwardState : public UMovementBaseState
{
	GENERATED_BODY()

public:
	virtual void Exit() override;
	virtual void Enter() override;
	virtual void Update() override;
	
	static FString StateName;

	virtual FString GetStateName() override;
};
