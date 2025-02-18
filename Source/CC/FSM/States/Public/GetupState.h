// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitReactionBaseState.h"
#include "UObject/Object.h"
#include "GetupState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UGetupState : public UHitReactionBaseState
{
	GENERATED_BODY()

public:
	static FString StateName;

	virtual FString GetStateName() override;
};
