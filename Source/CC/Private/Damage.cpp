// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage.h"
#include "Hwoarang.h"
#include "SteveFox.h"
#include "GameCharacterState.h"
#include "HitEffectStruct.h"
#include "Engine/Engine.h"

auto UDamage::ApplyDamage(ACharacter* Attacker, ACharacter* Defender, int32 MoveID) 
{
	if (!Attacker || !Defender)
	{
		return;
	}

	AHwoarang* HwoarangDefender = Cast<AHwoarang>(Defender);
	ASteveFox* SteveFoxDefender = Cast<ASteveFox>(Defender);

	FHitEffectStruct* HitEffects = GetHitEffectFromMoveID(MoveID);
    
	if (!HitEffects)  
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveID %d not found in HitEffect database"), MoveID);
		return;
	}

	float FinalDamage = HitEffects->ExtraDamage;

	if (HwoarangDefender)
	{
		HwoarangDefender->HP -= FinalDamage;
		HwoarangDefender->SetState(EGameCharacterState::Hit);
	}
	else if (SteveFoxDefender)
	{
		SteveFoxDefender->HP -= FinalDamage;
		SteveFoxDefender->SetState(EGameCharacterState::Hit);
	}

	UE_LOG(LogTemp, Log, TEXT("%s hit %s for %f damage"), 
		   *Attacker->GetName(), *Defender->GetName(), FinalDamage);
}