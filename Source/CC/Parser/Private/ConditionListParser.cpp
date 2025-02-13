#include "ConditionListParser.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "ConditionStruct.h"
#include "FastLogger.h"

std::map<int32, FConditionStruct> UConditionListParser::ConditionMap;

UConditionListParser::UConditionListParser()
{
}

// CSV 한 줄을 파싱하는 함수
std::vector<std::string> UConditionListParser::ParseCSVLine(const std::string& Line)
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

std::string UConditionListParser::RestoreJson(const std::string& CsvJson)
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

void UConditionListParser::ParseData()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "DataTable/ConditionListTable.csv";
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

		LineTokens = ParseCSVLine(Line);
		
		if (FirstLine)
		{
			FirstLine = false;
			continue;
		}

		if (LineTokens.size() != 8)
		{
			continue;
		}

		FConditionStruct Condition;
		Condition.ConditionID = std::atoi(LineTokens[0].c_str());
		Condition.ConditionName = LineTokens[1].c_str();
		Condition.ConditionChecker = LineTokens[2].c_str();
		Condition.ConditionData = RestoreJson(LineTokens[3]).c_str();
		Condition.ConditionGroup = LineTokens[4].c_str();
		Condition.bInvert = LineTokens[5] == "TRUE" ? true : false;
		Condition.Priority = std::atoi(LineTokens[6].c_str());

		ConditionMap[Condition.ConditionID] = Condition;
	}

	InputFile.close();

	for (auto& Pair : ConditionMap)
	{
		FFastLogger::LogConsole(TEXT("ConditionID: %d, ConditionName: %s, ConditionChecker: %s, ConditionData: %s, ConditionGroup: %s, bInvert: %d, Priority: %d"),
			Pair.first, *Pair.second.ConditionName, *Pair.second.ConditionChecker, *Pair.second.ConditionData, *Pair.second.ConditionGroup, Pair.second.bInvert, Pair.second.Priority);
	}
}

const FConditionStruct* UConditionListParser::GetConditionData(int32 ConditionID)
{
	if (ConditionMap.find(ConditionID) != ConditionMap.end())
	{
		return &ConditionMap[ConditionID];
	}
	return nullptr;
}
