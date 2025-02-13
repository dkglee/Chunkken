#pragma once

#include <map>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MoveComboParser.generated.h"

struct MoveNode
{
	int32 MoveID;
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

	virtual void BeginDestroy() override;
private:
	void LogMoveTree(MoveNode* Node, const FString& Indent);
	void PrintMoveTree();
	void InitMoveTree();
	void InitTree(const std::vector<int32>& Children, MoveNode** Parent);
	void DeleteMoveTree(MoveNode* Node);
	void ClearMoveTree();


	std::map<int32, std::vector<int32>> ParsedMap;
	static std::map<int32, MoveNode*> MoveTree;
};
