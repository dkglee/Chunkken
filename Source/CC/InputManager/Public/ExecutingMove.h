#pragma once

#include "CoreMinimal.h"
#include "ExecutingMove.generated.h"

USTRUCT(BlueprintType)
struct FExecutingMove
{
	GENERATED_BODY()

	// MoveID가 -1 일시 이동
	int32 MoveID = 0;
	uint64 FrameIndex = 0;
	// bIgnore가 true일 시 무시 모든 입력 무시
	bool bIgnore = false;
	// bCombDone이 true일 시 콤보가 끝남
	bool bCombDone = false;
};
