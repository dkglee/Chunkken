// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackBaseState.h"
#include "UObject/Object.h"
#include "AttackStartupState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UAttackStartupState : public UAttackBaseState
{
	GENERATED_BODY()

public:
	static FString StateName;

	virtual FString GetStateName() override;
};
