// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CrouchingBaseState.h"
#include "UObject/Object.h"
#include "CrouchingWalkState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UCrouchingWalkState : public UCrouchingBaseState
{
	GENERATED_BODY()

public:
	static FString StateName;

	virtual FString GetStateName() override;
};
