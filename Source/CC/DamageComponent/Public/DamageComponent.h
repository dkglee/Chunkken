// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveDataStruct.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CC_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDamageComponent();

	void TakeDamage(int32 Damage);
	void UpdateHitCombo(const FMoveDataStruct* MoveData);
	void UpdateHitReaction(class ABaseCharacter* Target, const FMoveDataStruct* MoveData);
	void UpdateHitInfo(class ABaseCharacter* Target);
	bool DetectCollision(const FString& SocketName);

protected:
	virtual void BeginPlay() override;
	void ResetHitCombo();

	UPROPERTY()
	class ABaseCharacter* Me = nullptr;

	UPROPERTY()
	float SphereRadius = 25.0f;

	UPROPERTY()
	int32 HP = 100.0f;

	UPROPERTY()
	int32 HitCombo = 0;

	UPROPERTY()
	FTimerHandle HitComboResetTimer;

	UPROPERTY()
	float HitComboResetDelay = 2.0f;
};
