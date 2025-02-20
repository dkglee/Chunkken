#pragma once

#include "CoreMinimal.h"
#include "MoveDataStruct.h"
#include "Components/ActorComponent.h"
#include "Damage.generated.h"

class ACharacter;
class UCollision;
class UDataTable;
struct FHitEffectStruct;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CC_API UDamage : public UActorComponent
{
	GENERATED_BODY()

public:
	UDamage();

protected:
	virtual void BeginPlay() override;

public:
	// 데미지 적용
	void ApplyDamage(ACharacter* Attacker, ACharacter* Defender, int32 MoveID);

	FMoveDataStruct* MoveDataStructs;
};
