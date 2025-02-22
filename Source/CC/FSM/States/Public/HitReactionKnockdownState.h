// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitReactionBaseState.h"
#include "UObject/Object.h"
#include "HitReactionKnockdownState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UHitReactionKnockdownState : public UHitReactionBaseState
{
	GENERATED_BODY()

public:
	static FString StateName;

	virtual void Exit() override;
	virtual void Enter() override;
	virtual void Update() override;

	virtual FString GetStateName() override;

protected:
	// TEST
	UPROPERTY()
	FTimerHandle TimerHandle;
};
