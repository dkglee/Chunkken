#pragma once

#include "CoreMinimal.h"
#include "ECameraSequence.generated.h"

UENUM(BlueprintType)
enum class ECameraSequence : uint8
{
	ECS_None,
	ECS_KO,
	ECS_Airbone,
	ECS_StrongHit,
	ECS_WeakHit,
};
