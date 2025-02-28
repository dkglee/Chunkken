// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveDataStruct.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"

#define MAX_NS_SIZE 10
#define MAX_HIT_LEVEL_UI 10

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CC_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDamageComponent();

	int32 TakeDamage(int32 Damage);
	bool DetectCollision(const FString& InSocketName);
	void ReleaseEffect(class UNiagaraComponent* NiagaraComponent, int32 Index);
	void ReleaseUI(class UHitLevelUI* HitLevelUI, int32 Index);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void ResetHitCombo();
	void ChangeColor(UNiagaraComponent* HitNS, const FMoveDataStruct* MoveData);
	void SpawnHitEffect(const FMoveDataStruct* MoveData);
	void UpdateHitInfo(const FMoveDataStruct* MoveData);
	void UpdateHitInfoUI(const FMoveDataStruct* MoveData);
	void UpdateHitReaction(class ABaseCharacter* Target, const FMoveDataStruct* MoveData);
	void SpawnHitLevelUI(const FMoveDataStruct* MoveData);
	void UpdateHitInfo(class ABaseCharacter* Target);

	UPROPERTY()
	class ABaseCharacter* Me = nullptr;

	UPROPERTY()
	float SphereRadius = 100.0f;

	UPROPERTY()
	int32 HP = 300.0f;
	UPROPERTY()
	int32 MaxHP = 300.0f;

	UPROPERTY()
	int32 HitCombo = 0;
	UPROPERTY()
	int32 HitDamage = 0;

	UPROPERTY()
	FTimerHandle HitInfoResetTimer;

	UPROPERTY()
	float HitInfoResetDelay = 1.0f;

	UPROPERTY()
	TArray<class UNiagaraComponent*> HitEffectsComponents;

	UPROPERTY()
	class UNiagaraSystem* HitEffectSystem = nullptr;
	UPROPERTY()
	TArray<FTimerHandle> HitEffectTimers;

	UPROPERTY()
	FString SocketName;

	UPROPERTY()
	class UMainUI* MainUI = nullptr;

	UPROPERTY()
	TArray<class UHitLevelUI*> HitLevelUIs;
	UPROPERTY()
	TArray<FTimerHandle> HitLevelUITimers;
	UPROPERTY()
	TSubclassOf<class UHitLevelUI> HitLevelUIClass;

	UPROPERTY()
	class ACameraManager* CameraManager = nullptr;
	UPROPERTY()
	class UTekkenCameraShakeManager* CameraShakeManager = nullptr;

	UPROPERTY()
	class USoundCue* HitSound = nullptr;
	UPROPERTY()
	class USoundCue* KOSound = nullptr;
};
