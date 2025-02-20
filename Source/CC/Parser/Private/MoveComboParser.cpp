#include "MoveComboParser.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "FastLogger.h"
#include "MoveDataStruct.h"
#include "MoveParser.h"

std::map<int32, MoveNode*> UMoveComboParser::MoveTree;

void UMoveComboParser::LogMoveTree(MoveNode* Node, const FString& Indent)
{
	if (!Node) return;

	// 현재 노드 출력
	UE_LOG(LogTemp, Warning, TEXT("%s├── MoveID: %d , %d"), *Indent, Node->MoveID, Node->AnimID);

	// 자식 노드를 재귀적으로 출력
	for (auto& [MoveID, ChildNode] : Node->Children)
	{
		LogMoveTree(ChildNode, Indent + TEXT("|  "));
	}
}

void UMoveComboParser::PrintMoveTree()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveTree Structure:"));

	for (auto& [RootID, RootNode] : MoveTree)
	{
		LogMoveTree(RootNode, TEXT(""));
	}
}

UMoveComboParser::UMoveComboParser()
{
}

void UMoveComboParser::ParserData()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "DataTable/MoveComboTable.csv";
	std::ifstream InputFile(TCHAR_TO_ANSI(*InputFilePath));

	if (!InputFile.is_open())
	{
		FFastLogger::LogConsole(TEXT("Failed to open file: %s"), *InputFilePath);
		return;
	}

	std::string Line;
	bool FirstLine = true;

	while (std::getline(InputFile, Line))
	{
		std::stringstream LineStream(Line);
		std::string Token;
		std::vector<std::string> LineTokens;

		while (std::getline(LineStream, Token, ','))
		{
			LineTokens.push_back(Token);
		}

		if (FirstLine)
		{
			FirstLine = false;
			continue;
		}

		if (LineTokens.size() != 4)
		{
			continue;
		}

		int32 ParentID = std::atoi(LineTokens[0].c_str());
		int32 StepOrder = std::atoi(LineTokens[1].c_str());
		int32 MoveID = std::atoi(LineTokens[2].c_str());
		int32 AnimID = std::atoi(LineTokens[3].c_str());
		FFastLogger::LogConsole(TEXT("AnimID - Parser : %d"), AnimID);

		// FFastLogger::LogConsole(TEXT("%d %d %d"), ParentID, StepOrder, MoveID);
		ParsedMap[ParentID].push_back({MoveID, AnimID});
	}

	InputFile.close();

	InitMoveTree();

	PrintMoveTree();
}

bool UMoveComboParser::IsMoveIdInCombo(const TArray<FExecutingMove>& Moveset, int32 MoveID, int32& AnimID)
{
	int32 StartMoveID = Moveset[0].MoveID;
	if (MoveTree.find(StartMoveID) == MoveTree.end())
	{
		return false;
	}
	MoveNode* Root = MoveTree[StartMoveID];
	for (int i = 1; i < Moveset.Num(); i++)
	{
		int32 MoveIDInLoop = Moveset[i].MoveID;
		if (Root->Children.find(MoveIDInLoop) == Root->Children.end())
		{
			return false;
		}
		Root = Root->Children[MoveIDInLoop];
	}
	bool bIsInCombo = Root->Children.contains(MoveID);
	if (bIsInCombo)
	{
		AnimID = Root->Children[MoveID]->AnimID;
	}
	return bIsInCombo;
}

void UMoveComboParser::BeginDestroy()
{
	ClearMoveTree();
	Super::BeginDestroy();
}

void UMoveComboParser::InitMoveTree()
{
	for (auto& [ParentID, Children] : ParsedMap)
	{
		int32 StartIndex = Children[0].first;
		int32 StartAnimID = Children[0].second; 

		MoveNode* Root;
		if (MoveTree.find(StartIndex) == MoveTree.end())
		{
			Root = new MoveNode();
			Root->MoveID = StartIndex;
			Root->AnimID = StartAnimID;
			MoveTree[StartIndex] = Root;
		}
		else
		{
			Root = MoveTree[StartIndex];
		}

		InitTree(Children, &Root);	
	}
}

void UMoveComboParser::InitTree(const std::vector<std::pair<int32, int32>>& Children, MoveNode** Parent)
{
	MoveNode* StartNode = *Parent;

	for (int i = 1; i < Children.size(); i++)
	{
		int32 MoveID = Children[i].first;
		int32 AnimID = Children[i].second;
		if (StartNode->Children.find(MoveID) == StartNode->Children.end())
		{
			// 없음
			MoveNode* Node = new MoveNode();
			Node->MoveID = MoveID;
			Node->AnimID = AnimID;
			StartNode->Children[MoveID] = Node;
			StartNode = Node;
		}
		else
		{
			StartNode = StartNode->Children[MoveID];
		}
	}
}

void UMoveComboParser::DeleteMoveTree(MoveNode* Node)
{
	if (!Node) return;

	// 자식 노드들 먼저 삭제
	for (auto& [MoveID, ChildNode] : Node->Children)
	{
		DeleteMoveTree(ChildNode);
	}

	// 노드 삭제
	delete Node;
}

void UMoveComboParser::ClearMoveTree()
{
	// 모든 루트 노드에 대해 메모리 해제
	for (auto& [MoveID, RootNode] : MoveTree)
	{
		DeleteMoveTree(RootNode);
	}

	MoveTree.clear();
}