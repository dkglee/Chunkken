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

		if (LineTokens.size() != 8)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid row with %llu columns"), LineTokens.size());
			continue;
		}

		FTransitionListDataStruct Transition;

		Transition.TransitionID = std::atoi(LineTokens[0].c_str());
		Transition.FromStateID = std::atoi(LineTokens[1].c_str());
		Transition.bParentStateCheck = (LineTokens[2] == "TRUE") ? true : false;
		Transition.ConditionLogic = ParserConditionLogic(LineTokens[3]);
		Transition.ConditionIDs = ParserConditionIDs(LineTokens[4]);
		Transition.ToStateID = std::atoi(LineTokens[5].c_str());
		Transition.Priority = std::atoi(LineTokens[6].c_str());

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

EConditionLogic UTransitionParser::ParserConditionLogic(std::string LineToken)
{
	if (LineToken == "AND") return EConditionLogic::AND;
	if (LineToken == "OR") return EConditionLogic::OR;
	if (LineToken == "NOT") return EConditionLogic::NOT;
	return EConditionLogic::NONE;
}

TArray<int32> UTransitionParser::ParserConditionIDs(std::string LineToken)
{
	std::stringstream LineStream(LineToken);
	std::string Token;

	TArray<int32> ConditionIDs;

	while (std::getline(LineStream, Token, '|'))
	{
		ConditionIDs.Add(std::atoi(Token.c_str()));
	}
	
	return ConditionIDs;
}

/** TransitionMap의 모든 데이터를 출력하는 함수 */
void UTransitionParser::PrintTransitionMap()
{
    if (TransitionMap.empty())
    {
        UE_LOG(LogTemp, Warning, TEXT("TransitionMap is empty!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("========= Transition Map ========="));

    for (const auto& Pair : TransitionMap)
    {
        const FTransitionListDataStruct& Transition = Pair.second;

        // ConditionLogic을 문자열로 변환
        FString ConditionLogicStr;
        switch (Transition.ConditionLogic)
        {
        case EConditionLogic::NONE: ConditionLogicStr = TEXT("None"); break;
        case EConditionLogic::AND:  ConditionLogicStr = TEXT("AND"); break;
        case EConditionLogic::OR:   ConditionLogicStr = TEXT("OR"); break;
        case EConditionLogic::NOT:  ConditionLogicStr = TEXT("NOT"); break;
        default: ConditionLogicStr = TEXT("Unknown"); break;
        }

        // ConditionIDs(TArray<int32>)를 쉼표로 구분된 문자열로 변환
        FString ConditionIDsStr;
        for (int32 i = 0; i < Transition.ConditionIDs.Num(); ++i)
        {
            ConditionIDsStr += FString::Printf(TEXT("%d"), Transition.ConditionIDs[i]);
            if (i < Transition.ConditionIDs.Num() - 1)
            {
                ConditionIDsStr += TEXT(", ");
            }
        }

        // 최종 출력 문자열 생성
        FString Output = FString::Printf(
            TEXT("ID: %d, From: %d, To: %d, ParentCheck: %s, Logic: %s, ConditionIDs: [%s], Priority: %d, Action: %s"),
            Transition.TransitionID,
            Transition.FromStateID,
            Transition.ToStateID,
            Transition.bParentStateCheck ? TEXT("True") : TEXT("False"),
            *ConditionLogicStr,
            *ConditionIDsStr,
            Transition.Priority,
            *Transition.OnTransitionAction
        );

        // 콘솔 로그 출력
    	FFastLogger::LogConsole(TEXT("%s"), *Output);
    }
}
