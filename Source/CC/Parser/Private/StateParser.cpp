#include "StateParser.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "FastLogger.h"
#include "StateDataStruct.h"

std::map<int32, FStateDataStruct> UStateParser::StateMap;

UStateParser::UStateParser()
{
}

// CSV 한 줄을 파싱하는 함수
std::vector<std::string> UStateParser::ParseCSVLine(const std::string& Line)
{
    std::vector<std::string> Tokens;
    std::string CurrentField;
    bool bInsideQuotes = false;

    for (size_t i = 0; i < Line.length(); ++i)
    {
        char c = Line[i];

        if (c == '"')
        {
            bInsideQuotes = !bInsideQuotes;
        }
        else if (c == ',' && !bInsideQuotes)
        {
            Tokens.push_back(CurrentField);
            CurrentField.clear();
        }
        else
        {
            CurrentField += c;
        }
    }

    Tokens.push_back(CurrentField);
    return Tokens;
}

void UStateParser::ParseData()
{
    // CSV 파일 경로 설정
    FString InputFilePath = FPaths::ProjectContentDir() + TEXT("DataTable/StateListTable.csv");
    std::ifstream InputFile(TCHAR_TO_ANSI(*InputFilePath));

    if (!InputFile.is_open())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to open file: %s"), *InputFilePath);
        return;
    }

    std::string Line;
    bool bIsFirstLine = true;

    int LineCount = 0;
    while (std::getline(InputFile, Line))
    {
        if (bIsFirstLine)
        {
            bIsFirstLine = false;
            continue;
        }
        
        std::vector<std::string> LineTokens = ParseCSVLine(Line);

        if (LineTokens.size() < 8)
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid row with %d columns"), LineTokens.size());
            continue;
        }

        if (LineTokens[0].empty())
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid StateID"));
            continue;
        }

        FStateDataStruct State;
        State.StateID = std::atoi(LineTokens[0].c_str());
        State.Name = FString(LineTokens[1].c_str()).ToUpper();
        State.StateGroup = FString(LineTokens[2].c_str()).ToUpper();
        State.DefaultDuration = std::atoi(LineTokens[3].c_str());
        State.AnimationRef = FString(LineTokens[4].c_str()).ToUpper();
        State.OnEnterAction = FString(LineTokens[5].c_str());
        State.OnExitAction = FString(LineTokens[6].c_str());
        State.ExtraData = FString(LineTokens[7].c_str());
        
        StateMap[State.StateID] = State;
        LineCount++;
    }

    InputFile.close();
}