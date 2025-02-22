// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"

#include "BaseCharacter.h"
#include "FastLogger.h"
#include "HitEffectParser.h"
#include "HitEffectStruct.h"
#include "MoveDataStruct.h"
#include "MoveParser.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
}

void UDamageComponent::TakeDamage(int32 Damage)
{
	HP -= Damage;
	if (HP <= 0)
	{
		// 죽음 처리
		// FSM에서 죽음 상태로 변경
	}
}

void UDamageComponent::UpdateHitCombo(const FMoveDataStruct* MoveData)
{
	HitCombo += MoveData->Hits;

	// UI에 표시되는 Combo를 업데이트
	GetWorld()->GetTimerManager().ClearTimer(HitComboResetTimer);
	GetWorld()->GetTimerManager().SetTimer(HitComboResetTimer, this, &UDamageComponent::ResetHitCombo, HitComboResetDelay, false);
}

// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	Me = Cast<ABaseCharacter>(GetOwner());
}

void UDamageComponent::ResetHitCombo()
{
	HitCombo = 0;
	// UI에 표시되는 Combo를 초기화
}

// SphereTrace를 활성화 하는 함수
bool UDamageComponent::DetectCollision(const FString& SocketName)
{
	FVector Start = Me->GetMesh()->GetSocketLocation(*SocketName);
	FVector End   = Start + (Me->GetActorForwardVector() * 100.0f);
	
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(Me);
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, Start, SphereRadius, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResult, true);

	if (!HitResult.bBlockingHit)
	{
		FFastLogger::LogScreen(FColor::Cyan, TEXT("No Hit"));
		return false;
	}

	ABaseCharacter* Target = Cast<ABaseCharacter>(HitResult.GetActor());
	if (!Target)
	{
		return false;
	}

	// 전반적으로 계산하는 로직을 처리
	UpdateHitInfo(Target);
	
	return true;
}

void UDamageComponent::UpdateHitInfo(class ABaseCharacter* Target)
{
	FExecutingMove ExecutingMove = Me->CurrentExecutingMove;
	const FMoveDataStruct* MoveData = UMoveParser::GetMoveDataByMoveID(ExecutingMove.MoveID);
	if (!MoveData)
	{
		FFastLogger::LogConsole(TEXT("MoveData is nullptr in UpdateHitInfo"));
		return;
	}

	UDamageComponent* TargetDamageComponent = Target->GetDamageComponent();
	if (!TargetDamageComponent)
	{
		FFastLogger::LogConsole(TEXT("TargetDamageComponent is nullptr in UpdateHitInfo"));
		return;
	}

	if (Target->CharacterState.bCanBeDamaged == false)
	{
		FFastLogger::LogConsole(TEXT("Target cannot be damaged"));
		return;
	}

	TargetDamageComponent->TakeDamage(MoveData->Damage); // 데미지 적용
	// 아래에 계속해서 추가적인 작업을 함. (HitReaction 등) 근데 죽음 이후에 아래의 처리를 하는 것이 과연 옳을까? 근데 상관 없음
	// 왜냐하면 FSM의 우선순위를 두면 되기 때문임

	// Hit Combo 처리 (UI에 표시) : 시간이 지나면 사라짐
	UpdateHitCombo(MoveData);
	UpdateHitReaction(Target, MoveData);
}

void UDamageComponent::UpdateHitReaction(ABaseCharacter* Target, const FMoveDataStruct* MoveData)
{
	int32 HitEffectID = UHitEffectParser::GetHitEffectByMoveID(MoveData->MoveID);
	const FHitEffectStruct* HitEffect = UHitEffectParser::GetHitEffect(HitEffectID);
	if (!HitEffect)
	{
		FFastLogger::LogConsole(TEXT("HitEffect is nullptr in UpdateHitReaction"));
		return;
	}

	FString HitReaction = HitEffect->HitReaction;
	// Upper로 변경 후 비교
	
	if (HitReaction.ToUpper().Contains(TEXT("NONE")) || HitReaction.ToUpper().Contains(FString(TEXT("NoAdvantage")).ToUpper()) || HitReaction.ToUpper().Contains(FString(TEXT("TailSpin")).ToUpper()))
	{
		return;
	}

	Target->CharacterState.HitReaction = HitReaction;
	Target->CharacterState.HitAnimInfo = {MoveData->HitLevel, MoveData->SocketID};

	// UI에 HitLevel 표시 : High, Mid, Low
	return ;
}
