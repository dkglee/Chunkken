#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Collision.generated.h"

class UBoxComponent;
class ACharacter;
class UDataTable;
struct FHitEffectStruct;



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CC_API UCollision : public UActorComponent
{
	GENERATED_BODY()

public:
	UCollision();

protected:
	virtual void BeginPlay() override;

public:
	// 공격 활성화 여부
	bool bAttackActive;

	// 캐릭터의 공격 판정 박스들 (손, 발 등)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	TArray<UBoxComponent*> HitBoxes;

	// 기존 DataTable을 활용하여 충돌 범위 조회
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	UDataTable* ExistingDataTable;




	// 공격 활성화 시 충돌 감지
	//void ActivateCollision(bool bActivate, int32 MoveID);

	// 충돌 감지 (기존 DataTable에서 MoveID 기반으로 히트박스 설정)
	bool CheckCollision(ACharacter* Attacker, ACharacter* Defender, int32 MoveID);
};
