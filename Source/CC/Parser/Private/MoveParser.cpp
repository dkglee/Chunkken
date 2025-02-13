#include "MoveParser.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <bitset>

#include "FastLogger.h"
#include "MoveDataStruct.h"
#include "CC.h"
#include "InputParser.h"

std::map<CharID, std::map<uint64, MoveID>> UMoveParser::MoveIDMap;
std::map<CharID, std::map<MoveID, FMoveDataStruct>> UMoveParser::MoveDataMap;
std::map<MoveID, FMoveDataStruct> UMoveParser::MoveDataMapByMoveID;

UMoveParser::UMoveParser()
{
}


FString UMoveParser::ConvertBitmaskToBinary(uint64 Bitmask)
{
	return FString(ANSI_TO_TCHAR(std::bitset<64>(Bitmask).to_string().c_str()));
}


uint64 UMoveParser::ParseCommand(std::string LineToken)
{
	uint64 Command = 0;
	std::stringstream CommandStream(LineToken);
	std::string Token;

	while (std::getline(CommandStream, Token, '|'))
	{
		// 단타 단위로 나뉘어짐
		uint64 Bitmask = CalculateBitmask(Token);
		// TODO : 트리로도 저장해야 함.
		Command |= Bitmask;
		Command <<= 8;
	}
	Command >>= 8;
	
	return Command;
}

unsigned char UMoveParser::CalculateBitmask(std::string LineToken)
{
	unsigned char Bitmask = 0;
	std::stringstream BitmaskStream(LineToken);
	std::string Token;

	while (std::getline(BitmaskStream, Token, '+'))
	{
		// f : right
		// b : left
		if (Token == "f")
			Token = RIGHT;
		if (Token == "b")
			Token = LEFT;
		std::ranges::transform(Token, Token.begin(), [](unsigned char c) { return std::toupper(c); });
		int32 Index = UInputParser::GetIndex(Token);
		unsigned char Bit = UInputParser::GetBitmask(Index);
		Bitmask |= Bit;
	}
	return Bitmask;
}

void UMoveParser::ParserData()
{
	FString InputFilePath = FPaths::ProjectContentDir() + "DataTable/MoveTable.csv";
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

		if (LineTokens.size() != 14)
		{
			continue;
		}

		FMoveDataStruct MoveData;
		MoveData.MoveID = std::atoi(LineTokens[0].c_str());
		MoveData.CharID = std::atoi(LineTokens[1].c_str());
		MoveData.Command = ParseCommand(LineTokens[2]);
		MoveData.RelativeID = std::atoi(LineTokens[3].c_str());
		MoveData.AttackType = FString(LineTokens[4].c_str()).ToUpper();
		MoveData.Damage = std::atoi(LineTokens[5].c_str());
		MoveData.Hits = std::atoi(LineTokens[6].c_str());
		MoveData.HitLevel = FString(LineTokens[7].c_str()).ToUpper();
		MoveData.StartUp = std::atoi(LineTokens[8].c_str());
		MoveData.ActiveFrames = std::atoi(LineTokens[9].c_str());
		MoveData.Recovery = std::atoi(LineTokens[10].c_str());
		MoveData.OnBlock = std::atoi(LineTokens[11].c_str());
		MoveData.OnHit = std::atoi(LineTokens[12].c_str());

		MoveIDMap[MoveData.CharID][MoveData.Command] = MoveData.MoveID;
		MoveDataMap[MoveData.CharID][MoveData.MoveID] = MoveData;
		MoveDataMapByMoveID[MoveData.MoveID] = MoveData;
	}

	InputFile.close();

	for (auto& [CharID, MoveData] : MoveDataMap)
	{
		for (auto& [MoveID, Data] : MoveData)
		{
			FFastLogger::LogConsole(TEXT("MoveID: %d, CharID: %d, Command: (Bitmask: %llu, Binary: %s), RelativeID: %d, AttackType: %s, Damage: %d, Hits: %d, HitLevel: %s, StartUp: %d, ActiveFrames: %d, Recovery: %d, OnBlock: %d, OnHit: %d"),
				Data.MoveID, Data.CharID, Data.Command, *ConvertBitmaskToBinary(Data.Command),
				Data.RelativeID, *Data.AttackType, Data.Damage, Data.Hits, *Data.HitLevel, Data.StartUp, Data.ActiveFrames, Data.Recovery, Data.OnBlock, Data.OnHit);
		}
	}
}

MoveID UMoveParser::GetMoveID(CharID CharID, uint64 Command)
{
	if (MoveIDMap.find(CharID) == MoveIDMap.end())
	{
		return -1;
	}
	if (MoveIDMap[CharID].find(Command) == MoveIDMap[CharID].end())
	{
		return -1;
	}
	return MoveIDMap[CharID][Command];
}

const FMoveDataStruct* UMoveParser::GetMoveData(CharID CharID, MoveID MoveID)
{
	if (MoveDataMap.find(MoveID) == MoveDataMap.end())
	{
		return nullptr;
	}
	if (MoveDataMap[MoveID].find(MoveID) == MoveDataMap[MoveID].end())
	{
		return nullptr;
	}
	return &(MoveDataMap[MoveID][MoveID]);
}

const FMoveDataStruct* UMoveParser::GetMoveDataByMoveID(MoveID MoveID)
{
	if (MoveDataMapByMoveID.find(MoveID) == MoveDataMapByMoveID.end())
	{
		return nullptr;
	}
	return &(MoveDataMapByMoveID[MoveID]);;
}
