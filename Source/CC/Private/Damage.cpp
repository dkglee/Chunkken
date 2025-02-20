#include "Damage.h"

#include "BaseCharacter.h"
#include "HitEffectParser.h"
#include "HitEffectStruct.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Actor.h"
#include "HitEffectStruct.h"
#include "MoveParser.h"

UDamage::UDamage()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDamage::BeginPlay()
{
	Super::BeginPlay();
}

void UDamage::ApplyDamage(ACharacter* Attacker, ACharacter* Defender, int32 MoveID)
{
	if (!Attacker || !Defender)
	{
		UE_LOG(LogTemp, Error, TEXT("데미지 적용 실패- 공격자 또는 피격자가 없다."));
		return;
	}

	ABaseCharacter* AttackerCharacter = Cast<ABaseCharacter>(Attacker);
	ABaseCharacter* DefenderCharacter = Cast<ABaseCharacter>(Defender);

	if (!AttackerCharacter || !DefenderCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("데미지 적용 실패- 캐릭터가 없다."));
		return;
	}
	
	int32 MoveIDKey = UHitEffectParser::GetHitEffectByMoveID(MoveID);
	const FHitEffectStruct* MoveData = UHitEffectParser::GetHitEffect(MoveIDKey);
	if (!AttackerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("데미지 적용 실패- DataTable이 없다."));
		return;
	}

	
	const FMoveDataStruct* GameMoveDataStruct = UMoveParser::GetMoveDataByMoveID(MoveID);

	if (!GameMoveDataStruct)
	{
		UE_LOG(LogTemp, Error, TEXT("데미지 적용 실패- MoveID %d를 DataTable에서 찾을 수 없다."), MoveID);
		return;
	}

	// 데미지 적용
	float FinalDamage =MoveDataStructs->Damage;
	DefenderCharacter->HP -= FinalDamage;
	
	UE_LOG(LogTemp, Log, TEXT("데미지 적용- %s 가(이) %s 에게 MoveID %d 공격으로 %f 데미지 적용. 남은 체력: %d"),*AttackerCharacter->GetName(), *DefenderCharacter->GetName(), MoveID, FinalDamage, DefenderCharacter->HP);
}