#pragma once

#include <map>

#include "CoreMinimal.h"
#include "TransitionListDataStruct.h"
#include "UObject/Object.h"
#include "TransitionParser.generated.h"

UCLASS()
class UTransitionParser : public UObject
{
	GENERATED_BODY()
public:
	UTransitionParser();

	UFUNCTION()
	void ParseData();

	static const FTransitionListDataStruct* GetTransitionData(int32 TransitionID);

	virtual void BeginDestroy() override;
	
protected:
	struct FLogicNode* ParseExpression();
	struct FLogicNode* ParseOr();
	struct FLogicNode* ParseAnd();
	struct FLogicNode* ParsePrimitive();
	FString GetToken();
	FString PeekToken();

	void PrintLogicNodeRecursive(FLogicNode* Node, int Depth = 0);
	void PrintTransitionMap();
	void ClearTransitionMap();
	void DestroyLogicNode(FLogicNode* Node);
	

	TArray<FString> SplitString(const FString& Source);

	static std::map<int32, FTransitionListDataStruct> TransitionMap;

	UPROPERTY()
	int32 IndexAST;
	UPROPERTY()
	TArray<FString> Tokens;
};
