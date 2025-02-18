// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "UObject/Object.h"
#include "AttackBaseState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UAttackBaseState : public UBaseState
{
	GENERATED_BODY()

	virtual FString GetStateName() override;
};
