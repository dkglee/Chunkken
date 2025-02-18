// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameHitEffectStruct.h"
#include "Components/ActorComponent.h"
#include "Damage.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CC_API UDamage : public UActorComponent
{
	GENERATED_BODY()

public:
	static FHitEffectStruct* GetHitEffectFromMoveID(int32 INT32);
	
	UFUNCTION(BlueprintCallable, Category="Damage")
	static void ApplyDamage(ACharacter* Attacker, ACharacter* Defender, int32 MoveID);
};