#include "SocketParser.h"

#include <fstream>
#include <sstream>
#include <string>

#include "FastLogger.h"

std::map<int32, FString> USocketParser::SocketMap;

USocketParser::USocketParser()
{
}

void USocketParser::ParseData()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "DataTable/SocketTable.csv";
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

		int32 SocketID = std::atoi(LineTokens[0].c_str());
		FString SocketName = LineTokens[1].c_str();

		SocketMap[SocketID] = SocketName;
	}

	InputFile.close();
}

FString USocketParser::GetSocketName(int32 SocketID)
{
	if (SocketMap.find(SocketID) == SocketMap.end())
	{
		return "";
	}
	return SocketMap[SocketID];
}
