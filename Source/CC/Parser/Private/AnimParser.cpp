#include "AnimParser.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "FastLogger.h"

std::map<int32, FAnimationDataStruct> UAnimParser::AnimationDataMap;

UAnimParser::UAnimParser()
{
}

void UAnimParser::ParseData()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "DataTable/AnimationTable.csv";
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

		if (LineTokens.size() != 2)
		{
			continue;
		}

		FAnimationDataStruct AnimData;
		AnimData.AnimID = std::atoi(LineTokens[0].c_str());
		AnimData.AnimName = LineTokens[1].c_str();

		AnimationDataMap[AnimData.AnimID] = AnimData;
	}

	for (auto& Pair : AnimationDataMap)
	{
		FFastLogger::LogConsole(TEXT("AnimID: %d, AnimName: %s"), Pair.first, *Pair.second.AnimName);
	}
	
	InputFile.close();
}

const FAnimationDataStruct* UAnimParser::GetAnimData(int32 AnimID)
{
	if (auto FindData = AnimationDataMap.find(AnimID); FindData != AnimationDataMap.end())
	{
		return &FindData->second;
	}
	return nullptr;
}
