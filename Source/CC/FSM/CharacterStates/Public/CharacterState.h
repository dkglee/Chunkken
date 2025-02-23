#pragma once

#include "CoreMinimal.h"
#include "CharacterState.generated.h"

USTRUCT(BlueprintType)
struct FCharacterState
{
	GENERATED_BODY()

	// 이동 입력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	bool bForward = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	bool bBackward = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	bool bJump = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	bool bCrouching = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	bool bAttack = false;

	// 캐릭터 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	bool bGround = true;

	// 공격 중에 다음 공격이 실행될 수 있는가를 나타냄
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	bool bAttackAvailable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	bool bCanBeDamaged = true;

	// 이거는 FSM에서 다뤄져야 함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	bool bFrameOver = false;

	// 히트 리액션 (피격 상태) : 공격 이벤트가 들어오면 다뤄져야 함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HitReaction")
	FString HitReaction = "";

	// 이전 상태 (상태 머신 용도) : FSM에서 State가 변경될 때 다뤄져야 함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StateMachine")
	FString PrevState = "";

	// 더블탭 입력 타이밍 : 임시
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	int32 TapInterval = 0;

	// 방향 정보 : Legacy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	FString Direction = "";

	std::pair<FString, int32> HitAnimInfo = {TEXT(""), 0};
	int32 HitStun = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	bool bKO = false;
};
