#include "MovesParser.h"
#include "Misc/DateTime.h"

// TArray<uint8> UMovesParser::InputBuffer;
// int32 UMovesParser::MaxBufferSize = 1024;

//입력 버퍼
// void UMovesParser::AddInput(uint8 NewInput)
// {
// 	if (InputBuffer.Num() >= MaxBufferSize)
// 	{
// 		InputBuffer.RemoveAt(0);
// 	}
//
// 	InputBuffer.Add(NewInput);
//
// 	UE_LOG(LogTemp, Log, TEXT("Input Added: %d"), NewInput);
// }

//버퍼 분석 -> 기술 찾기
// FMoveData UMovesParser::ParseInputBuffer(UDataTable* MoveTable)
// {
// 	FMoveData DefaultMove;
//
// 	if (!MoveTable || InputBuffer.Num() == 0)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("MoveTable is NULL or InputBuffer is empty!"));
// 		return DefaultMove;
// 	}
//
// 	
// 	static const FString ContextString(TEXT("Move Data Context"));
// 	TArray<FName> RowNames = MoveTable->GetRowNames();
//
// 	for (const FName& Name : RowNames)
// 	{
// 		FMoveData* Move = MoveTable->FindRow<FMoveData>(Name, ContextString);
// 		if (Move)
// 		{
// 			return *Move; // 구조체 복사하여 반환
// 		}
// 	}
// 	return DefaultMove;
// }
