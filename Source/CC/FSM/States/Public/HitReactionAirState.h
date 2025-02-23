// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitReactionBaseState.h"
#include "UObject/Object.h"
#include "HitReactionAirState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UHitReactionAirState : public UHitReactionBaseState
{
	GENERATED_BODY()

public:
	static FString StateName;

	virtual void Exit() override;
	virtual void Enter() override;
	virtual void Update() override;

	virtual FString GetStateName() override;

protected:
	std::pair<FString, int32> HitAnimData;

	UPROPERTY()
	FTimerHandle TimerHandle;
	UPROPERTY()
	float MaxHeight = 200.0f;

	UPROPERTY()
	bool bIsGrounded = false;
	UPROPERTY()
	int32 MaxFrameAirBorne = 30;
	UPROPERTY()
	int32 CurrentFrameAirBorne = 0;
	UPROPERTY()
	FVector Location;
};
