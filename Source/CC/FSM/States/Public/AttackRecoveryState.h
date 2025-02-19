// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackBaseState.h"
#include "UObject/Object.h"
#include "AttackRecoveryState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UAttackRecoveryState : public UAttackBaseState
{
	GENERATED_BODY()

public:
	static FString StateName;
	
	virtual void Exit() override;
	virtual void Enter() override;
	virtual void Update() override;

	virtual FString GetStateName() override;
};
