// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Deque.h"
#include "InputManager.generated.h"

#define MAX_INPUT_QUEUE 60

USTRUCT(BlueprintType)
struct FInputEventPerFrame
{
	GENERATED_BODY();

	int32 CharID = 0;
	unsigned char BitMask = 0;
	uint64 FrameIndex = 0;
	bool bLeft = false;
	bool bUsed = false;
};

// 캐릭터당 하나씩 존재하는 인풋 매니저
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CC_API UInputManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UInputManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void PushOnPressedInput(int32 CharID, int32 InputID, uint64 FrameIndex, bool bLeft);
	UFUNCTION()
	void PushOnReleasedInput(int32 CharID, int32 InputID, uint64 FrameIndex, bool bLeft);
	UFUNCTION()
	int32 ExtractMoveIdFromInput(const TArray<int32>& Moveset);
private:
	UFUNCTION()
	void StoreInputEvent(FInputEventPerFrame InputEvent);
	UFUNCTION()
	void UpdateInputEvent(FInputEventPerFrame InputEvent);
	UFUNCTION()
	int32 GetInputEvenIndex(uint64 FrameIndex);
	
	UPROPERTY()
	TArray<FInputEventPerFrame> InputQueue;

	UPROPERTY()
	int32 CurrentQueueIndex = 0;
};
