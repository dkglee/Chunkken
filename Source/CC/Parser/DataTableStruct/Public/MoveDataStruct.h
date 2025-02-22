#pragma once

#include "CoreMinimal.h"
#include "MoveDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FMoveDataStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MoveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharID;

	UPROPERTY(EditAnywhere)
	uint64 Command;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RelativeID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Hits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HitLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StartUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ActiveFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Recovery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OnBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OnHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AnimID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SocketID;
};
