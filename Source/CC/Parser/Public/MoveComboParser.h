#pragma once

#include <map>

#include "CoreMinimal.h"
#include "ExecutingMove.h"
#include "UObject/Object.h"
#include "MoveComboParser.generated.h"

struct MoveNode
{
	int32 MoveID;
	int32 AnimID;
	int32 SocketID;
	std::map<int32, struct MoveNode*> Children;
};

UCLASS()
class UMoveComboParser : public UObject
{
	GENERATED_BODY()
public:
	UMoveComboParser();

	UFUNCTION()
	void ParserData();

	static bool IsMoveIdInCombo(const TArray<FExecutingMove>& Moveset, int32 MoveID, int32& AnimID);
	
	virtual void BeginDestroy() override;
private:
	void LogMoveTree(MoveNode* Node, const FString& Indent);
	void PrintMoveTree();
	void InitMoveTree();
	void InitTree(const std::vector<MoveNode>& Children, MoveNode** Parent);
	void DeleteMoveTree(MoveNode* Node);
	void ClearMoveTree();
	
	std::map<int32, std::vector<MoveNode>> ParsedMap;
	static std::map<int32, MoveNode*> MoveTree;
};
