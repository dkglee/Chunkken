#pragma once

#include "CoreMinimal.h"
#include "FastLogger.generated.h"

USTRUCT()
struct FFastLogger
{
	GENERATED_BODY()

	// 화면에 메시지 출력
	template<typename FmtType, typename... Arg>
	static void LogScreen(FColor Color, const FmtType& Format, Arg&&... Args_)
	{
		const FString LogMessage = FString::Printf(Format, std::forward<Arg>(Args_)...);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, Color, LogMessage);
		}
	}

	// 파일에 메시지 저장
	template<typename FmtType, typename... Arg>
	static void LogFile(const FString& FileName, const FmtType& Format, Arg&&... Args)
	{
		const FString FormattedMessage = FString::Printf(Format, std::forward<Arg>(Args)...);

		FString FilePath = FPaths::ProjectDir() + FileName;

		IFileManager& FileManager = IFileManager::Get();

		TUniquePtr<FArchive> FileWriter(FileManager.CreateFileWriter(*FilePath, EFileWrite::FILEWRITE_Append));
		if (FileWriter)
		{
			FString DataToWrite = FormattedMessage + LINE_TERMINATOR; // 줄바꿈 추가
			FileWriter->Serialize(TCHAR_TO_ANSI(*DataToWrite), DataToWrite.Len());
			FileWriter->Close();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to open file: %s"), *FilePath);
		}
	}

	// 콘솔에 메시지 출력
	template<typename FmtType, typename... Arg>
	static void LogConsole(const FmtType& Format, Arg&&... Args)
	{
		const FString FormattedMessage = FString::Printf(Format, std::forward<Arg>(Args)...);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FormattedMessage);
	}
};