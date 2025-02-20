#include "BaseCharacter.h"
#include "CC/Public/Collision.h"
#include "CC/Public/Damage.h" 
#include "CC.h"
#include "GameCharacterState.h"
#include "InputManager.h"
#include "InputParser.h"
#include "TekkenFSM.h"
#include "CC/TekkenAnimInstance/Public/TekkenAnimIntance.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EngineUtils.h"

ABaseCharacter::ABaseCharacter()
{
	GetCharacterMovement()->bRunPhysicsWithNoController = false;

	InputManager = CreateDefaultSubobject<UInputManager>(TEXT("InputManager"));
	TekkenFSM = CreateDefaultSubobject<UTekkenFSM>(TEXT("TekkenFSM"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_AnimInstace
	(TEXT("/Game/Animations/ABP_TekkenAnimInstace.ABP_TekkenAnimInstace_C"));
	if (ABP_AnimInstace.Succeeded())
	{
		TekkenAnimClass = ABP_AnimInstace.Class;
	}

	GetMesh()->SetAnimInstanceClass(TekkenAnimClass);

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	

	// 체력 기본 값 설정
	HP = 100;
	
	// 컴포넌트 생성
	CollisionComponent = CreateDefaultSubobject<UCollision>(TEXT("CollisionComponent"));
	DamageComponent = CreateDefaultSubobject<UDamage>(TEXT("DamageComponent"));
	
	// 히트박스 설정
	//HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox1 = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox1"));
	HitBox1->SetupAttachment(GetMesh(),TEXT("hand_lSocket"));
	HitBox1->SetBoxExtent(FVector(15.0f,15.0,15.0f));
	
	HitBox2 = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox2"));
	HitBox2->SetupAttachment(GetMesh(),TEXT("hand_rSocket"));
	HitBox2->SetBoxExtent(FVector(15.0f,15.0,15.0f));
	
	HitBox3 = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox3"));
	HitBox3->SetupAttachment(GetMesh(),TEXT("foot_lSocket"));
	HitBox3->SetBoxExtent(FVector(15.0f,15.0,15.0f));
	
	HitBox4 = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox4"));
	HitBox4->SetupAttachment(GetMesh(),TEXT("foot_rSocket"));
	HitBox4->SetBoxExtent(FVector(15.0f,15.0,15.0f));

	//HitBoxes.Add(HitBox);
	HitBoxes.Add(HitBox1);
	HitBoxes.Add(HitBox2);
	HitBoxes.Add(HitBox3);
	HitBoxes.Add(HitBox4);
	
	// 허트박스 설정
	HurtBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HurtBox"));
	HurtBox->SetupAttachment(GetMesh(),TEXT("spine_01Socket"));
	HurtBox->SetBoxExtent(FVector(30.0f,30.0,100.0f));
	HurtBoxes.Add(HurtBox);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HitBox)
	{
		HitBox->IgnoreActorWhenMoving(this, true);
	}

	if (HurtBox)
	{
		HurtBox->IgnoreActorWhenMoving(this, true);
	}
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
	CharacterState.bForward = false;
	CharacterState.bBackward = false;
	CharacterState.bJump = false;
	CharacterState.bCrouching = false;
	CharacterState.bGround = GetCharacterMovement()->IsMovingOnGround();
	CharacterState.bCanBeDamaged = true;
	CharacterState.bAttack = false;
	
	// Update Input
	InputManager->PushEmptyInput(CharID, FrameIndex, CharID == 102 ? true : false);
	FExecutingMove ExecutingMove = InputManager->ExtractMoveIdFromInput(Moveset);
	
	UpdateMovement(FrameIndex, ExecutingMove);
	UpdateAttack(FrameIndex, ExecutingMove);
	ClearMoveset();
	
	// Update FSM
	TekkenFSM->Update(FrameIndex);
}

UBaseState* ABaseCharacter::GetCurrentState()
{
	return TekkenFSM->GetCurrentState();
}

class USubFSM* ABaseCharacter::GetSubFSM()
{
	return TekkenFSM->GetCurrentFSM();
}

float ABaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


void ABaseCharacter::UpdateMovement(uint64 FrameIndex, const FExecutingMove& ExecutingMove)
{
	// TODO : bIgnore
	// 무시하는 상황은 콤보가 진행중인데 다른 입력이 들어온 상황을 의미함.
	if (ExecutingMove.bIgnore)
	{
		return ;
	}
	
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
}

// TODO: Movement하고 Attack을 순차적으로 실행 시켜야 함. 왜냐하면 CharacterState는 계속해서 업데이트 되어야 함.
// 현재 실행중인 ExecutingMove를 찾아야 함.
void ABaseCharacter::UpdateAttack(uint64 FrameIndex, const FExecutingMove& ExecutingMove)
{
	// if (ExecutingMove.bIgnore)
	// {
	// 	return ;
	// }
	//
	// if (ExecutingMove.MoveID == -1)
	// {
	// 	CharacterState.bAttack = false;
	// 	return ;
	// }

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
}

void ABaseCharacter::ClearMoveset()
{
	// 그럼 언제 Moveset을 초기화 해야 할까?
	// TODO: 공격 당했을 때! & 강제 초기화
	// MoveIndex가 Moveset의 크기보다 크거나 같을 때!
	// 공격이 끝났을 때!
	if (bResetMoveSet && MoveIndex >= Moveset.Num())
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

void ABaseCharacter::PerformAttack(int32 MoveID)
{
	if (!CollisionComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("[공격 실패] 충돌 컴포넌트가 없습니다."));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("[공격 실행] %s 가(이) MoveID %d 공격을 실행합니다."), *GetName(), MoveID);
	CurrentMoveID = MoveID;
	CollisionComponent->CheckCollision(this, nullptr, MoveID);  // 충돌 검사
}
// TODO: Movement하고 Attack을 순차적으로 실행 시켜야 함. 왜냐하면 CharacterState는 계속해서 업데이트 되어야 함.