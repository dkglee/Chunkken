// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitReactionBaseState.h"
#include "UObject/Object.h"
#include "HitReactionNormalState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UHitReactionNormalState : public UHitReactionBaseState
{
	GENERATED_BODY()

public:
	static FString StateName;

	virtual void Exit() override;
	virtual void Enter() override;
	virtual void Update() override;

	virtual FString GetStateName() override;

protected:
	void PlayAnimation(const FString& String, int32 INT32);
	
	std::pair<FString, int32> HitAnimData;
	FTimerHandle TimerHandle;
	int32 StunFrame;
};
