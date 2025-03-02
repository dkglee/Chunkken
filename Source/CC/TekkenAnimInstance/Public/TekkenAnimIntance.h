// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExecutingMove.h"
#include "Animation/AnimInstance.h"
#include "TekkenAnimIntance.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UTekkenAnimIntance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UTekkenAnimIntance();
	
	UFUNCTION()
	virtual void AnimNotify_RestartMovement();
	UFUNCTION()
	virtual void AnimNotify_ResetFrame();
	UFUNCTION()
	virtual void AnimNotify_ComboRestart();
	UFUNCTION()
	virtual void AnimNotify_CameraShake();
	UFUNCTION()
	virtual void PlayMontageModule(const FString& MontageName, float InPlayRate = 1.0f, FName StartSectionName = NAME_None);
	UFUNCTION(BlueprintImplementableEvent, Category = "PlayAnim")
	void PlayMontage(class UAnimMontage* Montage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None);

	class UAnimMontage* GetMontageFromName(const FString& String);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
	TMap<FString, class UAnimMontage*> MontageMap;
	UPROPERTY()
	class ACameraManager* CameraManager = nullptr;
	UPROPERTY()
	class UTekkenCameraShakeManager* CameraShakeManager = nullptr;
};
