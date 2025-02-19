// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JumpBaseState.h"
#include "UObject/Object.h"
#include "JumpStartState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UJumpStartState : public UJumpBaseState
{
	GENERATED_BODY()

public:
	static FString StateName;

	virtual void Exit() override;
	virtual void Enter() override;
	virtual void Update() override;
	
	virtual FString GetStateName() override;
protected:
	UPROPERTY()
	FString MontageName = TEXT("JUMP");
};
