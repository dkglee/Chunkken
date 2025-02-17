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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	bool bAttackAvailable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	bool bCanBeDamaged = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	bool bFrameOver = false;

	// 히트 리액션 (피격 상태)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HitReaction")
	FString HitReaction = "";

	// 이전 상태 (상태 머신 용도)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StateMachine")
	FString PrevState = "";

	// 더블탭 입력 타이밍
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	int32 TapInterval = 0;

	// 방향 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	FString Direction = "";
};
