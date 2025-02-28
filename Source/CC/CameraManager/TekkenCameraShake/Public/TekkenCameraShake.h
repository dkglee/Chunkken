// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ECameraSequence.h"
#include "Components/ActorComponent.h"
#include "TekkenCameraShake.generated.h"

UCLASS()
class CC_API UTekkenCameraShakeManager : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UTekkenCameraShakeManager();

	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	void LoadCameraShakeClass(ECameraSequence SequenceType, const FSoftObjectPath& ObjectPath);

	UFUNCTION(BlueprintCallable, Category = CameraShake)
	void PlayerCameraShake(ECameraSequence CameraSequence, float Intensity);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraShake)
	TMap<ECameraSequence, TSubclassOf<UCameraShakeBase>> CameraShakeSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraShake)
	APlayerController* PlayerController = nullptr;
};
