#include "HitEffectParser.h"

#include <fstream>
#include <sstream>
#include <vector>

#include "HitEffectStruct.h"
#include "FastLogger.h"

std::map<int32, FHitEffectStruct> UHitEffectParser::HitEffectMap;
std::map<int32, int32> UHitEffectParser::HitEffetIDMap;

UHitEffectParser::UHitEffectParser()
{
}

void UHitEffectParser::ParseData()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "DataTable/HitEffectTable.csv";
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

		if (LineTokens.size() != 8)
		{
			continue;
		}

		FHitEffectStruct HitEffect;
		HitEffect.HitEffectID = std::atoi(LineTokens[0].c_str());
		HitEffect.MoveID = std::atoi(LineTokens[1].c_str());
		HitEffect.Condition = LineTokens[2].c_str();
		HitEffect.Condition = HitEffect.Condition.ToUpper();
		HitEffect.ExtraDamage = std::atoi(LineTokens[3].c_str());
		HitEffect.Launch = std::atoi(LineTokens[4].c_str());
		HitEffect.StunFrames = std::atoi(LineTokens[5].c_str());
		HitEffect.HitReaction = LineTokens[6].c_str();
		HitEffect.HitReaction = HitEffect.HitReaction.ToUpper();

		HitEffectMap[HitEffect.HitEffectID] = HitEffect;
		HitEffetIDMap[HitEffect.MoveID] = HitEffect.HitEffectID;
	}

	InputFile.close();

	for (auto& Pair : HitEffectMap)
	{
		FFastLogger::LogConsole(TEXT("HitEffectID: %d, MoveID: %d, Condition: %s, ExtraDamage: %d, Launch: %d, StunFrames: %d, HitReaction: %s"),
			Pair.second.HitEffectID, Pair.second.MoveID, *Pair.second.Condition, Pair.second.ExtraDamage, Pair.second.Launch, Pair.second.StunFrames, *Pair.second.HitReaction);
	}
}
