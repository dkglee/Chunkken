#include "InputParser.h"

#include <fstream>
#include <sstream>
#include <vector>

void UInputParser::ParseInput()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "/Content/CSV/InputTable.csv";
	std::ifstream InputFile(TCHAR_TO_ANSI(*InputFilePath));

	if (!InputFile.is_open())
	{
		return;
	}

	std::string Line;
	
	bool FirstLine = true;
	
	while (std::getline(InputFile, Line))
	{
		std::stringstream LineStream(Line);
		std::string Token;
		std::vector<std::string> LineTokens;

		
	}
}
