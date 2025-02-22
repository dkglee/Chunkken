#include "InputManager.h"

#include "AnimParser.h"
#include "InputParser.h"
#include "CC.h"
#include "FastLogger.h"
#include "HLSLTypeAliases.h"
#include "MoveComboParser.h"
#include "MoveParser.h"

UInputManager::UInputManager()
{
}


// Called when the game starts
void UInputManager::BeginPlay()
{
	Super::BeginPlay();
	
	InputQueue.Empty();
	InputQueue.Reserve(MAX_INPUT_QUEUE);
	InputQueue.SetNum(MAX_INPUT_QUEUE);
	for (int i = 0; i < MAX_INPUT_QUEUE; i++)
	{
		InputQueue[i].CharID = 0;
		InputQueue[i].BitMask = 0;
		InputQueue[i].FrameIndex = 0;
		InputQueue[i].bLeft = false;
		InputQueue[i].bUsed = false;
		InputQueue[i].bIgnored = false;
	}
}

// 매 프레임마다 단위를 저장할 예정 : 한 프레임에 하나의 단위로 넣는게 좋겠지?
void UInputManager::PushOnPressedInput(int32 CharID, int32 InputID, uint64 FrameIndex, bool bLeft)
{
	// 인풋이 어떤 Bitmask로 들어오는지 확인해야함
	unsigned char BitMask = UInputParser::GetBitmask(InputID);

	// right가 front, left가 back : LeftPlayer
	// right가 back, left가 front : RightPlayer
	if (!bLeft)
	{
		if (BitMask == UInputParser::GetBitmask(UInputParser::GetIndex(LEFT)))
		{
			BitMask = UInputParser::GetBitmask(UInputParser::GetIndex(RIGHT));
		}
		else if (BitMask == UInputParser::GetBitmask(UInputParser::GetIndex(RIGHT)))
		{
			BitMask = UInputParser::GetBitmask(UInputParser::GetIndex(LEFT));
		}
	}

	FInputEventPerFrame InputEvent;
	InputEvent.CharID = CharID;
	InputEvent.BitMask = BitMask;
	InputEvent.FrameIndex = FrameIndex;
	InputEvent.bLeft = bLeft;
	InputEvent.bUsed = false;
	InputEvent.bIgnored = false;

	StoreInputEvent(InputEvent);
}

void UInputManager::PushOnReleasedInput(int32 CharID, int32 InputID, uint64 FrameIndex, bool bLeft)
{
	unsigned char BitMask = UInputParser::GetBitmask(InputID);

	if (!bLeft)
	{
		if (BitMask == UInputParser::GetBitmask(UInputParser::GetIndex(LEFT)))
		{
			BitMask = UInputParser::GetBitmask(UInputParser::GetIndex(RIGHT));
		}
		else if (BitMask == UInputParser::GetBitmask(UInputParser::GetIndex(RIGHT)))
		{
			BitMask = UInputParser::GetBitmask(UInputParser::GetIndex(LEFT));
		}
	}
	
	FInputEventPerFrame InputEvent;
	InputEvent.CharID = CharID;
	InputEvent.BitMask = BitMask;
	InputEvent.FrameIndex = FrameIndex;
	InputEvent.bLeft = bLeft;
	InputEvent.bUsed = false;
	InputEvent.bIgnored = false;

	UpdateInputEvent(InputEvent);
}

void UInputManager::StoreInputEvent(FInputEventPerFrame& InputEvent)
{
	int32 Index = GetInputEvenIndex(InputEvent.FrameIndex);

	if (Index == -1)
	{
		// 새로운 인풋이 들어왔을 때
		// 이전 인풋의 값에 BitMask를 업데이트 하고 넣어야 함
		int32 PrevIndex = CurrentQueueIndex - 1;
		if (PrevIndex < 0)
		{
			PrevIndex = MAX_INPUT_QUEUE - 1;
		}
		// 이전거 유지 필요 : 보니까 항상 일정하게 매 프레임마다 입력이 들어오는 처리가 안됨.
		InputEvent.BitMask |= InputQueue[PrevIndex].BitMask;
		InputQueue[CurrentQueueIndex] = InputEvent;
		CurrentQueueIndex = (CurrentQueueIndex + 1) % MAX_INPUT_QUEUE;
	}
	else
	{
		// 기존 인풋이 들어왔을 때
		// 해당 프레임에 속하는 BitMask를 업데이트 해야함.
		InputQueue[Index].BitMask |= InputEvent.BitMask;
	}
}

void UInputManager::UpdateInputEvent(FInputEventPerFrame InputEvent)
{
	int32 Index = GetInputEvenIndex(InputEvent.FrameIndex);
	if (Index == -1)
	{
		// 불가능한 경우 : 왜냐하면 눌러야 땔 수 가 있기 때문임
		check(false);
	}
	InputQueue[Index].BitMask &= ~InputEvent.BitMask;
}

int32 UInputManager::GetInputEvenIndex(uint64 FrameIndex)
{
	int32 Index = -1;
	
	for (int i = 0; i < InputQueue.Num(); i++)
	{
		if (InputQueue[i].FrameIndex == FrameIndex)
		{
			Index = i;
			break;
		}
	}
	return Index;
}

FExecutingMove UInputManager::ExtractFirstComboInput()
{
	FExecutingMove ExecutingMove;

	// Tick이 먼저 호출됨
	int32 CurrentIndex = CurrentQueueIndex - 2;
	if (CurrentIndex < 0)
	{
		CurrentIndex = MAX_INPUT_QUEUE - 1;
	}
	int32 PrevIndex = CurrentIndex - 1;
	if (PrevIndex < 0)
	{
		PrevIndex = MAX_INPUT_QUEUE - 1;
	}

	FInputEventPerFrame& CurrentInput = InputQueue[CurrentIndex];
	FInputEventPerFrame& PrevInput = InputQueue[PrevIndex];
	CurrentInput.bUsed = true;
	
	ExecutingMove.MoveID = -1;
	ExecutingMove.FrameIndex = CurrentInput.FrameIndex;
	ExecutingMove.bIgnore = false;

	// 이전의 비트를 들고와서 현재의 비트들이 계속해서 눌려져 있는지 확인해야 함. (공격 부분만 검증)
	// 1이라면? 이전에 눌려져 있었다는 것임.
	// 그럼 해당 부분을 꺼주면 됨
	unsigned char AttackBitMask = 0xF0;
	unsigned char CurrentBitMask = CurrentInput.BitMask & AttackBitMask;
	unsigned char PrevBitMask = PrevInput.BitMask & AttackBitMask;
	unsigned char NewBitMask = CurrentBitMask & PrevBitMask;
	unsigned char ResultBitMask = CurrentInput.BitMask ^ NewBitMask;

	// 이러면 이번 프레임에 새로 눌린 공격 입력들을 추출할 수 있음!
	// 해당 비트로 MoveID가 있는지 조회해야 함
	int32 MoveID = UMoveParser::GetMoveID(CurrentInput.CharID, ResultBitMask);
	ExecutingMove.MoveID = MoveID;
	if (MoveID != -1)
	{
		int32 AnimID = UMoveParser::GetMoveDataByMoveID(MoveID)->AnimID;
		const FAnimationDataStruct* AnimData = UAnimParser::GetAnimData(AnimID);
		if (AnimData)
		{
			ExecutingMove.AnimationRef = AnimData->AnimName;
		}
		const FMoveDataStruct* MoveData = UMoveParser::GetMoveDataByMoveID(MoveID);
		int32 SocketID = MoveData != nullptr ? MoveData->SocketID : -1;
		ExecutingMove.SocketID = SocketID;
	}
	
	return ExecutingMove;
}

FExecutingMove UInputManager::ExtractComboInput(const TArray<FExecutingMove>& Moveset)
{
	FExecutingMove ExecutingMove;

	// Tick이 먼저 호출됨
	int32 CurrentIndex = CurrentQueueIndex - 2;
	if (CurrentIndex < 0)
	{
		CurrentIndex = MAX_INPUT_QUEUE - 1;
	}
	int32 PrevIndex = CurrentIndex - 1;
	if (PrevIndex < 0)
	{
		PrevIndex = MAX_INPUT_QUEUE - 1;
	}

	FInputEventPerFrame& CurrentInput = InputQueue[CurrentIndex];
	FInputEventPerFrame& PrevInput = InputQueue[PrevIndex];
	CurrentInput.bUsed = true;
	
	ExecutingMove.FrameIndex = CurrentInput.FrameIndex;
	ExecutingMove.bIgnore = false;

	// 이전의 비트를 들고와서 현재의 비트들이 계속해서 눌려져 있는지 확인해야 함. (공격 부분만 검증)
	// 1이라면? 이전에 눌려져 있었다는 것임.
	// 그럼 해당 부분을 꺼주면 됨
	unsigned char CurrentBitMask = CurrentInput.BitMask;
	unsigned char PrevBitMask = PrevInput.BitMask;
	unsigned char NewBitMask = CurrentBitMask & PrevBitMask;
	unsigned char ResultBitMask = CurrentInput.BitMask ^ NewBitMask;
	
	int32 MoveID = UMoveParser::GetMoveID(CurrentInput.CharID, ResultBitMask);
	ExecutingMove.MoveID = MoveID;

	// 가장 최근에 눌린 공격 입력을 받아 프레임을 계산 후 무시 여부를 판단해야 함.
	int32 FirstFrameIndex = Moveset[0].FrameIndex;
	int32 FrameStartUp = 0;
	for (int i = 0; i < Moveset.Num(); i++)
	{
		const FMoveDataStruct* MoveData = UMoveParser::GetMoveDataByMoveID(Moveset[i].MoveID);
		FrameStartUp += MoveData->StartUp;
	}
	
	// MoveID가 -1이고 해당 입력이 콤보 인정 기간안에 실행되지 못했다면 무시해야 함.
	// 또한 콤보가 끝났다면 무시해야 함.
	int32 FrameDifference = CurrentInput.FrameIndex - (FirstFrameIndex + FrameStartUp);
	if (FrameDifference > 0 || MoveID == -1 || Moveset.Last().bCombDone == true)
	{
		ExecutingMove.bIgnore = true;
		return ExecutingMove;
	}

	// 콤보 안에 드는지 확인해야 함!
	int32 AnimId = -1;
	bool bIsInCombo = UMoveComboParser::IsMoveIdInCombo(Moveset, MoveID, AnimId);
	if (!bIsInCombo)
	{
		ExecutingMove.bIgnore = true;
		ExecutingMove.bCombDone = true;
	}

	const FAnimationDataStruct* AnimData = UAnimParser::GetAnimData(AnimId);
	if (AnimData)
	{
		ExecutingMove.AnimationRef = AnimData->AnimName;
	}
	const FMoveDataStruct* MoveData = UMoveParser::GetMoveDataByMoveID(MoveID);
	int32 SocketID = MoveData != nullptr ? MoveData->SocketID : -1;
	ExecutingMove.SocketID = SocketID;
	
	return ExecutingMove;
}

FExecutingMove UInputManager::ExtractMoveIdFromInput(TArray<FExecutingMove>& Moveset)
{
	FExecutingMove ExecutingMove;

	if (Moveset.Num() == 0)
	{
		ExecutingMove = ExtractFirstComboInput();
	}
	else
	{
		ExecutingMove = ExtractComboInput(Moveset);
	}
	
	if (ExecutingMove.MoveID != -1 && !ExecutingMove.bIgnore)
	{
		FFastLogger::LogScreen(FColor::Green, TEXT("MoveID: %d, FrameIndex: %d"), ExecutingMove.MoveID, ExecutingMove.FrameIndex);
		Moveset.Add(ExecutingMove);
	}
	
	// 콤보가 끝났다면 콤보 리스트에 업데이트 해줘야 함
	if (ExecutingMove.bCombDone)
	{
		Moveset[Moveset.Num() - 1].bCombDone = true;
	}
	
	return ExecutingMove;
}

void UInputManager::PushEmptyInput(int32 CharID, uint64 FrameIndex, bool bLeft)
{
	FInputEventPerFrame InputEvent;
	InputEvent.CharID = CharID;
	InputEvent.BitMask = 0;
	InputEvent.FrameIndex = FrameIndex;
	InputEvent.bLeft = bLeft;
	InputEvent.bUsed = false;
	InputEvent.bIgnored = false;

	StoreInputEvent(InputEvent);
}

uint8 UInputManager::GetCurrentIndexBitMask()
{
	// Tick이 입력보다 먼저 들어오는 문제가 있기 때문에 -2로 한것.
	int32 CurrentIndex = CurrentQueueIndex - 2;
	if (CurrentIndex < 0)
	{
		CurrentIndex = MAX_INPUT_QUEUE - 1;
	}
	uint8 BitMask = InputQueue[CurrentIndex].BitMask;
	return BitMask;
}
