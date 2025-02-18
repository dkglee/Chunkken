// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CrouchingBaseState.h"
#include "UObject/Object.h"
#include "CrouchingIdleState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UCrouchingIdleState : public UCrouchingBaseState
{
	GENERATED_BODY()

public:
	static FString StateName;

	virtual FString GetStateName() override;
};
