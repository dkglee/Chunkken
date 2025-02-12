#include "CharacterParser.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "CharacterDataStruct.h"
#include "FastLogger.h"

std::map<int32, FCharacterDataStruct> UCharacterParser::CharacterDataMap;

UCharacterParser::UCharacterParser()
{
}

void UCharacterParser::ParseData()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "DataTable/CharacterTable.csv";
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

		if (LineTokens.size() != 7)
		{
			continue;
		}

		FCharacterDataStruct CharData;
		CharData.CharID = std::atoi(LineTokens[0].c_str());
		CharData.CharName = LineTokens[1].c_str();
		CharData.Title = LineTokens[2].c_str();
		CharData.HP = std::atoi(LineTokens[3].c_str());
		CharData.BaseSpeed = std::atoi(LineTokens[4].c_str());
		CharData.WakeupSpeed = std::atoi(LineTokens[5].c_str());

		CharacterDataMap[CharData.CharID] = CharData;	
	}

	for (auto& Pair : CharacterDataMap)
	{
		FFastLogger::LogConsole(TEXT("CharID: %d, CharName: %s, Title: %s, HP: %d, BaseSpeed: %d, WakeupSpeed: %d"),
			Pair.second.CharID, *Pair.second.CharName, *Pair.second.Title, Pair.second.HP, Pair.second.BaseSpeed, Pair.second.WakeupSpeed);
	}
	
	InputFile.close();
}

const FCharacterDataStruct* UCharacterParser::GetCharacterData(int32 CharID)
{
	if (CharacterDataMap.find(CharID) == CharacterDataMap.end())
	{
		FFastLogger::LogConsole(TEXT("Character ID %d not found"), CharID);
		return nullptr;
	}
	return &CharacterDataMap[CharID];
}
