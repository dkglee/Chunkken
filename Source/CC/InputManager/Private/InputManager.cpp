#include "InputManager.h"

#include "InputParser.h"
#include "CC.h"

UInputManager::UInputManager()
{
}


// Called when the game starts
void UInputManager::BeginPlay()
{
	InputQueue.Empty();
	InputQueue.Reserve(MAX_INPUT_QUEUE);
	InputQueue.SetNum(MAX_INPUT_QUEUE);
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
		else
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
		else
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

	UpdateInputEvent(InputEvent);
}

void UInputManager::StoreInputEvent(FInputEventPerFrame InputEvent)
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
	if (Index != -1)
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

// 바로 실행 해줘야 하는디..!? 항상 이전 입력하고 비교 해야 하는구나..!
// 애니메이션 몽타주를 그때그때 판단해서 연속적으로 실행해주면 될듯!
int32 UInputManager::ExtractMoveIdFromInput(const TArray<int32>& Moveset)
{
	int32 MoveID = -1;

	// 여태까지 입력된 인풋을 비교해서 MoveID를 추출해야함

	// 현재 들어온 입력을 가지고 무엇을 해야 하는가를 판단해야 함!
	// 이전에 내가 실행했던 Moveset을 넘겨 받아야 함
	// 가장 최근에 사용되었던 것을 찾아야 함! CurrentQueueIndex와 bUsed를 적절히 사용

	// 이전에 사용한 것 부터 어떤 입력을 실행할 지 찾아야 함!
	
	
	
	return MoveID;
}
