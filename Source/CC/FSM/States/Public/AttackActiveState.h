// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackBaseState.h"
#include "UObject/Object.h"
#include "AttackActiveState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UAttackActiveState : public UAttackBaseState
{
	GENERATED_BODY()

public:
	virtual void Exit() override;
	virtual void Enter() override;
	virtual void Update() override;
	
	static FString StateName;

	virtual FString GetStateName() override;

protected:
	int32 EndCount = 0;
	int32 EndFrame = 0;
};
