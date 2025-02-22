#pragma once

#include "CoreMinimal.h"

struct FExecutingMove
{
	// MoveID가 -1 이면 이동
	int32 MoveID = 0;
	uint64 FrameIndex = 0;
	// bIgnore가 true일 시 무시 모든 입력 무시
	bool bIgnore = false;
	// bCombDone이 true일 시 콤보가 끝남
	bool bCombDone = false;
	FString AnimationRef = "";
	int32 SocketID = -1;
};
