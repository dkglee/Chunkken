#include "ComboParser.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "ComboDataStruct.h"
#include "FastLogger.h"
#include "MoveParser.h"

std::map<int32, FComboDataStruct> UComboParser::ComboMap;

void UComboParser::PrintComboMap()
{
	for (const auto& [ComboID, ComboData] : ComboMap)
	{
		// ComboData의 기본 정보 출력
		FFastLogger::LogConsole(TEXT("ComboID: %d, CharID: %d, ComboName: %s, EstimatedDamage: %d"),
			ComboData.ComboID, ComboData.CharID, *ComboData.ComboName, ComboData.EstimatedDamage);

		// Notation 출력 (콤보 입력)
		FString NotationString = FString::JoinBy(ComboData.Notation, TEXT(","), [](int32 Num) { return FString::FromInt(Num); });
		FFastLogger::LogConsole(TEXT("Notation: %s"), *NotationString);

		// ComboDetails 출력
		for (const FComboDetailStruct& Detail : ComboData.ComboDetails)
		{
			FFastLogger::LogConsole(TEXT("  [Detail] StepOrder: %d, MoveID: %d, DashEvent: %s, TailSpinEvent: %s"),
				Detail.StepOrder, Detail.MoveID,
				Detail.bDashEvent ? TEXT("True") : TEXT("False"),
				Detail.bTailSpinEvent ? TEXT("True") : TEXT("False"));
		}

		FFastLogger::LogConsole(TEXT("-------------------------------------------------"));
	}
}


UComboParser::UComboParser()
{
}

void UComboParser::ParseData()
{
	ParseCombo();
	ParseComboDetail();
	PrintComboMap();
}

TArray<int32> UComboParser::ParseComboNotaion(int32 CharacterID, std::string LineToken)
{
	TArray<int32> Notation;

	std::stringstream NotationStream(LineToken);
	std::string Token;
	while (std::getline(NotationStream, Token, '|'))
	{
		int32 MoveId = std::atoi(Token.c_str());
		Notation.Add(MoveId);
	}
	return Notation;
}

void UComboParser::ParseCombo()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "DataTable/ComboTable.csv";
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

		if (LineTokens.size() != 6)
		{
			continue;
		}

		FComboDataStruct ComboData;
		ComboData.ComboID = std::atoi(LineTokens[0].c_str());
		ComboData.CharID = std::atoi(LineTokens[1].c_str());
		ComboData.ComboName = LineTokens[2].c_str();
		ComboData.Notation = ParseComboNotaion(ComboData.CharID, LineTokens[3]);	
		ComboData.EstimatedDamage = std::atoi(LineTokens[4].c_str());

		ComboMap[ComboData.ComboID] = ComboData;
	}

	InputFile.close();
}

void UComboParser::ParseComboDetail()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "DataTable/ComboDetailsTable.csv";
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

		if (LineTokens.size() != 5)
		{
			continue;
		}

		FComboDetailStruct ComboDetail;
		ComboDetail.ComboID = std::atoi(LineTokens[0].c_str());
		ComboDetail.StepOrder = std::atoi(LineTokens[1].c_str());
		ComboDetail.MoveID = std::atoi(LineTokens[2].c_str());
		ComboDetail.bDashEvent = LineTokens[3] == "TRUE" ? true : false;
		ComboDetail.bTailSpinEvent = LineTokens[4] == "TRUE" ? true : false;

		// Add ComboDetail to ComboMap
		ComboMap[ComboDetail.ComboID].ComboDetails.Add(ComboDetail);
	}

	InputFile.close();
}
