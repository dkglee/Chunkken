// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageComponent.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CC_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	AMyGameMode();

public:
	virtual void BeginPlay() override;
	class UMainUI* GetMainUI();
	bool IsGameStarted();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class AHwoarang>	HwoarangClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class ASteveFox>	SteveFoxClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class ACameraManager> CameraClass;

	UPROPERTY()
	TSubclassOf<class UMainUI> MainUIClass;

	UPROPERTY()
	class UMainUI* MainUI = nullptr;

	UPROPERTY()
	bool bGameStart = false;
};
