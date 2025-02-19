#pragma once

#include "CoreMinimal.h"
#include "TekkenAnimState.generated.h"

UENUM(BlueprintType)
enum class ETekkenAnimState : uint8
{
	Idle,
	Move,
	Jump,
	Crouch,
};