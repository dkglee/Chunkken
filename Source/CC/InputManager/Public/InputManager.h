// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Deque.h"
#include "ExecutingMove.h"
#include "InputManager.generated.h"

#define MAX_INPUT_QUEUE 60

USTRUCT(BlueprintType)
struct FInputEventPerFrame
{
	GENERATED_BODY();

	UPROPERTY()
	int32 CharID = 0;

	UPROPERTY()
	uint8 BitMask = 0;

	UPROPERTY()
	uint64 FrameIndex = 0;

	UPROPERTY()
	bool bLeft = false;

	UPROPERTY()
	bool bUsed = false;

	UPROPERTY()
	bool bIgnored = false;
};

// 캐릭터당 하나씩 존재하는 인풋 매니저
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CC_API UInputManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UInputManager();

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void PushOnPressedInput(int32 CharID, int32 InputID, uint64 FrameIndex, bool bLeft);
	UFUNCTION()
	void PushOnReleasedInput(int32 CharID, int32 InputID, uint64 FrameIndex, bool bLeft);
	FExecutingMove ExtractMoveIdFromInput(TArray<FExecutingMove>& Moveset);
	UFUNCTION()
	void PushEmptyInput(int32 CharID, uint64 FrameIndex, bool bLeft);
	UFUNCTION()
	uint8 GetCurrentIndexBitMask();
private:
	void StoreInputEvent(FInputEventPerFrame& InputEvent);
	void UpdateInputEvent(FInputEventPerFrame InputEvent);
	UFUNCTION()
	int32 GetInputEvenIndex(uint64 FrameIndex);
	FExecutingMove ExtractFirstComboInput();
	FExecutingMove ExtractComboInput(const TArray<FExecutingMove>& Moveset);
	
	TArray<FInputEventPerFrame> InputQueue;

	UPROPERTY()
	int32 CurrentQueueIndex = 0;
};
