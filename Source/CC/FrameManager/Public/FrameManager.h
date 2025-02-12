// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FrameManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CC_API UFrameManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFrameManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void UpdateFrame(float DeltaSeconds);
	uint64 GetFrameIndex() const;

private:
	uint64 FrameIndex = 0;
	double FrameTime = 0.0;
};
