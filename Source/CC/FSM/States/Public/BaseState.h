// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseState.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UBaseState : public UObject
{
	GENERATED_BODY()

public:	
	virtual void Initialize(class ABaseCharacter* InMe, class USubFSM* InOwnerFSM);

	UFUNCTION()
	virtual void Exit(){}
	UFUNCTION()
	virtual void Enter(){}
	UFUNCTION()
	virtual void Update(){}
	UFUNCTION()
	virtual FString GetStateName() { return TEXT(""); }
	UFUNCTION()
	void SetRestartMovement(bool bFlag);
	
protected:
	UPROPERTY()
	class ABaseCharacter* Me = nullptr;
	UPROPERTY()
	class USubFSM* OwnerFSM = nullptr;
	UPROPERTY()
	class UTekkenAnimIntance* TekkenAnimInstance = nullptr;
	UPROPERTY()
	bool bRestartMovement = true;
	UPROPERTY()
	class ACameraManager* CameraManager = nullptr;
	UPROPERTY()
	class UTekkenCameraShakeManager* CameraShakeManager = nullptr;
};
