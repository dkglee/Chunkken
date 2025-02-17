#include "TransitionParser.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "FastLogger.h"
#include "TransitionListDataStruct.h"

std::map<int32, FTransitionListDataStruct> UTransitionParser::TransitionMap;

UTransitionParser::UTransitionParser()
{
}

void UTransitionParser::ParseData()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "DataTable/TransitionListTable.csv";
	std::ifstream InputFile(TCHAR_TO_ANSI(*InputFilePath));
	
	if (!InputFile.is_open())
	{
		FFastLogger::LogConsole(TEXT("Failed to open file: %s"), *InputFilePath);
		return;
	}
	
	std::string Line;
	bool bIsFirstLine = true;

	while (std::getline(InputFile, Line))
	{
		std::stringstream LineStream(Line);
		std::string Token;
		std::vector<std::string> LineTokens;
		
		if (bIsFirstLine)
		{
			bIsFirstLine = false;
			continue;
		}
	
		while (std::getline(LineStream, Token, ','))
		{
			LineTokens.push_back(Token);
		}
	
		if (LineTokens.size() != 6)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid row with %llu columns"), LineTokens.size());
			continue;
		}
	
		FTransitionListDataStruct Transition;
	
		Transition.TransitionID = std::atoi(LineTokens[0].c_str());
		Transition.FromStateID = std::atoi(LineTokens[1].c_str());
		Tokens.Empty();
		IndexAST = 0;
		Tokens = SplitString(FString(ANSI_TO_TCHAR(LineTokens[2].c_str())));
		for (int32 i = 0; i < Tokens.Num(); i++)
		{
			if (Tokens[i] == "(" || Tokens[i] == ")" || Tokens[i] == "&" || Tokens[i] == "|")
			{
				continue;
			}
			Transition.ConditionTokens.Add(Tokens[i]);
		}
		Transition.ConditionLogic = ParseExpression();
		Transition.ToStateID = std::atoi(LineTokens[3].c_str());
		Transition.Priority = std::atoi(LineTokens[4].c_str());
	
		TransitionMap[Transition.TransitionID] = Transition;
	}

	InputFile.close();

	PrintTransitionMap();
}

const FTransitionListDataStruct* UTransitionParser::GetTransitionData(int32 TransitionID)
{
	if (TransitionMap.find(TransitionID) != TransitionMap.end())
	{
		return &TransitionMap[TransitionID];
	}
	return nullptr;
}

std::vector<FTransitionListDataStruct*> UTransitionParser::GetTransitionDataList(int32 FromStateID)
{
	std::vector<FTransitionListDataStruct*> TransitionList;
	for (const auto& Pair : TransitionMap)
	{
		const FTransitionListDataStruct& Transition = Pair.second;
		if (Transition.FromStateID == FromStateID)
		{
			TransitionList.push_back(&TransitionMap[Transition.TransitionID]);
		}
	}
	return TransitionList;
}

void UTransitionParser::BeginDestroy()
{
	ClearTransitionMap();
	Super::BeginDestroy();
}

/** TransitionMap의 모든 데이터를 출력하는 함수 */
void UTransitionParser::PrintLogicNodeRecursive(FLogicNode* Node, int Depth)
{
	if (!Node) return;

	// 들여쓰기 기반 트리 출력
	std::string Indent(Depth * 2, ' ');  // 공백 2개씩 반복
	UE_LOG(LogTemp, Log, TEXT("%s%s"), *FString(Indent.c_str()), *Node->Value);

	if (Node->Left) PrintLogicNodeRecursive(Node->Left, Depth + 1);
	if (Node->Right) PrintLogicNodeRecursive(Node->Right, Depth + 1);
}

void UTransitionParser::PrintTransitionMap()
{
	for (const auto& Pair : TransitionMap)
	{
		const FTransitionListDataStruct& Transition = Pair.second;

		UE_LOG(LogTemp, Warning, TEXT("Transition ID: %d"), Transition.TransitionID);
		UE_LOG(LogTemp, Warning, TEXT("  From State ID: %d"), Transition.FromStateID);
		UE_LOG(LogTemp, Warning, TEXT("  To State ID: %d"), Transition.ToStateID);
		UE_LOG(LogTemp, Warning, TEXT("  Priority: %d"), Transition.Priority);
		UE_LOG(LogTemp, Warning, TEXT("  On Transition Action: %s"), *Transition.OnTransitionAction);

		if (Transition.ConditionLogic)
		{
			UE_LOG(LogTemp, Warning, TEXT("  Condition Logic:"));
			PrintLogicNodeRecursive(Transition.ConditionLogic);
		}
	}
}

void UTransitionParser::ClearTransitionMap()
{
	for (auto& Pair : TransitionMap)
	{
		DestroyLogicNode(Pair.second.ConditionLogic);
	}
	TransitionMap.clear();
}

void UTransitionParser::DestroyLogicNode(FLogicNode* Node)
{
	if (!Node) return;

	DestroyLogicNode(Node->Left);
	DestroyLogicNode(Node->Right);

	delete Node;
}


FLogicNode* UTransitionParser::ParseExpression()
{
	return ParseOr();
}

TArray<FString> UTransitionParser::SplitString(const FString& Source)
{
	TArray<FString> InTokens;
	for (int32 i = 0; i < Source.Len(); i++)
	{
		TCHAR C = Source[i];

		if (FChar::IsWhitespace(C))
		{
			continue;
		}
		else if (C == '(' || C == ')' || C == '&' || C == '|')
		{
			InTokens.Add(FString(1, &C));
		}
		else if (C == '!')
		{
			InTokens.Add(FString(1, &C));
		}
		else
		{
			// Condition ID 파싱
			FString Token;
			while (i < Source.Len() && !FChar::IsWhitespace(Source[i]) && Source[i] != '(' && Source[i] != ')' && Source[i] != '&' && Source[i] != '|')
			{
				Token += Source[i];
				i++;
			}
			i--;
			InTokens.Add(Token);
		}
	}
	return InTokens;
}

FLogicNode* UTransitionParser::ParseOr()
{
	FLogicNode* Left = ParseAnd();
	while (PeekToken() == "|")
	{
		GetToken(); // Remove "|"
		FLogicNode* Right = ParseAnd();
		Left = new FLogicNode("|", Left, Right);
	}
	return Left;
}

FLogicNode* UTransitionParser::ParseAnd()
{
	FLogicNode* Left = ParsePrimitive();
	while (PeekToken() == "&")
	{
		GetToken(); // Remove "&"
		FLogicNode* Right = ParsePrimitive();
		Left = new FLogicNode("&", Left, Right);
	}
	return Left;
}

FLogicNode* UTransitionParser::ParsePrimitive()
{
	FString Token = GetToken();
	if (Token == "(")
	{
		FLogicNode* Node = ParseExpression();
		GetToken(); // Remove ")"
		return Node;
	}
	else if (Token == "!")
	{
		FLogicNode* Node = new FLogicNode(Token, ParsePrimitive(), nullptr);
		return Node;
	}
	else
	{
		FLogicNode* Node = new FLogicNode(Token, nullptr, nullptr);
		return Node;
	}
}

FString UTransitionParser::GetToken()
{
	return (IndexAST < Tokens.Num()) ? Tokens[IndexAST++] : "";
}

FString UTransitionParser::PeekToken()
{
	return (IndexAST < Tokens.Num()) ? Tokens[IndexAST] : "";
}
