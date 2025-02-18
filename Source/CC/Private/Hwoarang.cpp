#include "Hwoarang.h"

#include "Components/BoxComponent.h"


// Sets default values
AHwoarang::AHwoarang()
{
	AutoPossessPlayer = EAutoReceiveInput::Disabled;

	CharID = 102;

	// 체력 기본 값 설정
	HP = 100;

	// 히트박스 설정
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);

	// 허트박스 설정
	HurtBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HurtBox"));
	HurtBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHwoarang::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHwoarang::Attack()
{
	CurrentState = EGameCharacterState::Attacking;
}

void AHwoarang::SetState(EGameCharacterState NewState)
{
	CurrentState = NewState;
}