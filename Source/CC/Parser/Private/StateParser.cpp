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
    std::vector<std::string> Result;
    std::string Cell;
    bool inQuotes = false; // 따옴표 내부인지 여부

    for (size_t i = 0; i < Line.length(); i++) {
        char c = Line[i];

        if (c == '"') {
            inQuotes = !inQuotes;
            Cell += c;
        } else if (c == ',' && !inQuotes) {
            Result.push_back(Cell);
            Cell.clear();
        } else {
            Cell += c;
        }
    }
    Result.push_back(Cell);
    return Result;
}

std::string UStateParser::RestoreJson(const std::string& CsvJson)
{
    std::string Json = CsvJson;

    // CSV에서는 JSON의 따옴표가 ""로 저장되므로 이를 "로 변경
    size_t pos = 0;
    while ((pos = Json.find("\"\"", pos)) != std::string::npos) {
        Json.replace(pos, 2, "\""); // "" -> "
        pos += 1; // 다음 위치로 이동
    }

    // JSON의 시작과 끝에 따옴표가 있으므로 이를 제거
    Json = Json.substr(1, Json.length() - 2);
    return Json;
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

    while (std::getline(InputFile, Line))
    {
        if (bIsFirstLine)
        {
            bIsFirstLine = false;
            continue;
        }
        
        std::vector<std::string> LineTokens = ParseCSVLine(Line);

        if (LineTokens.size() != 7)
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
        State.ParentStateID = std::atoi(LineTokens[3].c_str());
        State.DefaultDuration = std::atoi(LineTokens[4].c_str());
        State.AnimationRef = FString(LineTokens[5].c_str()).ToUpper();
        
        StateMap[State.StateID] = State;
    }

    InputFile.close();

    // 전체 출력
    for (auto& Pair : StateMap)
    {
        FStateDataStruct& State = Pair.second;
        UE_LOG(LogTemp, Warning, TEXT("StateID: %d, Name: %s, StateGroup: %s, ParentStateID: %d, DefaultDuration: %d, AnimationRef: %s"),
            State.StateID, *State.Name, *State.StateGroup, State.ParentStateID, State.DefaultDuration, *State.AnimationRef);
    }
}