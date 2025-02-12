// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChunkkenGameMode.generated.h"

UCLASS()
class CC_API AChunkkenGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	AChunkkenGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	class AFrameManager* FrameManager;
};
