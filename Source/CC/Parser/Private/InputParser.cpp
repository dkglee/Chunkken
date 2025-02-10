#include "InputParser.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "CC/Utils/Public/FastLogger.h"

std::map<int32, unsigned char> UInputParser::InputMap;
std::unordered_map<std::string, int32> UInputParser::InputNameMap;

UInputParser::UInputParser()
{
}

void UInputParser::ParseData()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "DataTable/InputTable.csv";
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

		int32 Index = std::atoi(LineTokens[0].c_str());
		int32 BitIndex = std::atoi(LineTokens[2].c_str());
		InputMap[Index] = 1 << BitIndex;
		InputNameMap[LineTokens[1].c_str()] = Index;
	}
}
