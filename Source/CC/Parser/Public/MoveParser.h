#pragma once

#include <map>

#include "CoreMinimal.h"
#include "MoveDataStruct.h"
#include "MoveParser.generated.h"

typedef int32 MoveID;
typedef int32 CharID;

UCLASS()
class UMoveParser : public UObject
{
	GENERATED_BODY()
public:
	UMoveParser();

	UFUNCTION()
	void ParserData();

	static MoveID GetMoveID(CharID CharID, uint64 Command);
	static const FMoveDataStruct* GetMoveData(CharID CharID, MoveID MoveID);
	static const FMoveDataStruct* GetMoveDataByMoveID(MoveID MoveID);

protected:
	FString ConvertBitmaskToBinary(uint64 Bitmask);
	uint64 ParseCommand(std::string LineToken);
	unsigned char CalculateBitmask(std::string LineToken);

	// int32 : CharID
	// uint64 : Command
	// int32 : MoveID
	static std::map<CharID, std::map<uint64, MoveID>> MoveIDMap;
	static std::map<CharID, std::map<MoveID, FMoveDataStruct>> MoveDataMap;
	static std::map<MoveID, FMoveDataStruct> MoveDataMapByMoveID;
};
