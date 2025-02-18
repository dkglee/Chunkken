#include "BaseCharacter.h"

#include "CC.h"
#include "FastLogger.h"
#include "GameCharacterState.h"
#include "InputManager.h"
#include "InputParser.h"
#include "TekkenFSM.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseCharacter::ABaseCharacter()
{
	GetCharacterMovement()->bRunPhysicsWithNoController = false;

	InputManager = CreateDefaultSubobject<UInputManager>(TEXT("InputManager"));
	TekkenFSM = CreateDefaultSubobject<UTekkenFSM>(TEXT("TekkenFSM"));

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	

	// 체력 기본 값 설정
	HP = 100;

	// 히트박스 설정
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);

	// 허트박스 설정
	HurtBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HurtBox"));
	HurtBox->SetupAttachment(RootComponent);
}

void ABaseCharacter::OnPressedInput(int32 InputID, uint64 FrameIndex, bool bLeft)
{
	InputManager->PushOnPressedInput(CharID, InputID, FrameIndex, bLeft);
}

void ABaseCharacter::OnReleasedInput(int32 InputID, uint64 FrameIndex, bool bLeft)
{
	InputManager->PushOnReleasedInput(CharID, InputID, FrameIndex, bLeft);
}

void ABaseCharacter::Update(uint64 FrameIndex)
{
	// Update Input
	InputManager->PushEmptyInput(CharID, FrameIndex, CharID == 102 ? true : false);
	FExecutingMove ExecutingMove = InputManager->ExtractMoveIdFromInput(Moveset);
	
	if (ExecutingMove.bIgnore)
	{
		return ;
	}
	
	UpdateMovement(FrameIndex, ExecutingMove);
	UpdateAttack(FrameIndex, ExecutingMove);

	// Update FSM
	TekkenFSM->Update(FrameIndex);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::UpdateMovement(uint64 FrameIndex, const FExecutingMove& ExecutingMove)
{
	uint8 BitMask = InputManager->GetCurrentIndexBitMask();

	// 각 방향에 대한 입력 여부 확인
	bool bUp    = (BitMask & UInputParser::GetBitmask(UInputParser::GetIndex(UP))) != 0;
	bool bDown  = (BitMask & UInputParser::GetBitmask(UInputParser::GetIndex(DOWN))) != 0;
	bool bBack  = (BitMask & UInputParser::GetBitmask(UInputParser::GetIndex(LEFT))) != 0;
	bool bForward = (BitMask & UInputParser::GetBitmask(UInputParser::GetIndex(RIGHT))) != 0;

	// FFastLogger::LogScreen(FColor::Cyan, TEXT("CharID: %d, bUp: %d, bDown: %d, bBack: %d, bForward: %d"), CharID, bUp, bDown, bBack, bForward);
	
	// 위아래가 동시에 눌린 경우, 둘 다 무시
	if(bUp && bDown)
	{
		bUp = false;
		bDown = false;
	}

	// 앞뒤가 동시에 눌린 경우, 둘 다 무시
	if(bBack && bForward)
	{
		bBack = false;
		bForward = false;
	}

	// 수직 입력 처리 (우선 순위에 따라 처리 가능)
	if(bUp)
	{
		// 점프 처리
		this->Jump();
	}
	else if(bDown)
	{
		// 앉기 처리
		// this->Crouch();
	}

	// 이동 상태 저장
	CharacterState.bForward = bForward;
	CharacterState.bBackward = bBack;
	CharacterState.bJump = bUp;
	CharacterState.bCrouching = bDown;
	CharacterState.bGround = GetCharacterMovement()->IsMovingOnGround();
	CharacterState.bCanBeDamaged = true;

	if (ExecutingMove.MoveID != -1)
	{
		return ;
	}
	
	// 수평 입력 처리
	if(bForward)
	{
		// 전방 이동 처리
		FVector Direction = GetActorForwardVector();
		AddMovementInput(Direction, 0.6f);
	}
	else if(bBack)
	{
		// 후방 이동 처리
		FVector Direction = -GetActorForwardVector();
		AddMovementInput(Direction, 0.15f);
	}
    
	// 입력이 없으면 정지 처리
	if(!bUp && !bDown && !bBack && !bForward)
	{
		// 정지 처리
	}
}

// TODO: Movement하고 Attack을 순차적으로 실행 시켜야 함. 왜냐하면 CharacterState는 계속해서 업데이트 되어야 함.
// 현재 실행중인 ExecutingMove를 찾아야 함.
void ABaseCharacter::UpdateAttack(uint64 FrameIndex, const FExecutingMove& ExecutingMove)
{
	if (ExecutingMove.MoveID == -1)
	{
		CharacterState.bAttack = false;
		return ;
	}

	// 공격 가능한 상태인지 확인 (FSM에서 처리해줌) && 공격할 것이 남았는지 확인
	if (CharacterState.bAttackAvailable && MoveIndex < Moveset.Num())
	{
		CurrentExecutingMove = Moveset[MoveIndex++];
		CharacterState.bAttack = true;
	}
	else 
	{
		CharacterState.bAttack = false;
	}

	// 그럼 언제 Moveset을 초기화 해야 할까?
	// Attack Recovery가 온전히 끝나면 초기화 해야 함.
	// 해당 작업은 Animation Notify가 호출되고 FSM이 업데이트를 해줌.
	if (bResetMoveSet)
	{
		Moveset.Empty();
		MoveIndex = 0;
		bResetMoveSet = false;
	}
}

void ABaseCharacter::Attack()
{
	CurrentState = EGameCharacterState::Attacking;
}

void ABaseCharacter::SetState(EGameCharacterState NewState)
{
	CurrentState = NewState;
}