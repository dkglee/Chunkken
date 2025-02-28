#pragma once

#include "CoreMinimal.h"
#include "ECameraSequence.generated.h"

UENUM(BlueprintType)
enum class ECameraSequence : uint8
{
	ECS_None,
	ECS_Normal,
	ECS_Strong
};
