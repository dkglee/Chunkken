// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "UObject/Object.h"
#include "HitReactionBaseState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UHitReactionBaseState : public UBaseState
{
	GENERATED_BODY()

public:
	virtual void Exit() override;
	virtual void Enter() override;
	virtual void Update() override;

	virtual FString GetStateName() override;
};
