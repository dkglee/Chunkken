// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ChunkkenGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CC_API UChunkkenGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UChunkkenGameInstance();

	virtual void Init() override;

private:
	UPROPERTY()
	class UInputParser* InputParser;
	UPROPERTY()
	class UHitEffectParser* HitEffectParser;
	UPROPERTY()
	class UStateParser* StateParser;
	UPROPERTY()
	class UMoveParser* MoveParser;
	UPROPERTY()
	class UCharacterParser* CharacterParser;
};
