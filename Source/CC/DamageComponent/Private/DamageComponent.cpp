// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"

#include "BaseCharacter.h"
#include "FastLogger.h"
#include "HitEffectParser.h"
#include "HitEffectStruct.h"
#include "HitLevelUI.h"
#include "MainUI.h"
#include "MoveDataStruct.h"
#include "MoveParser.h"
#include "MyGameMode.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_Effect
	(TEXT("/Game/sA_ItemDropFx/Fx/NS_Epic_System.NS_Epic_System"));
	if (NS_Effect.Succeeded())
	{
		HitEffectSystem = NS_Effect.Object;
	}
	static ConstructorHelpers::FClassFinder<UHitLevelUI> WBP_HitLevelUIClass
	(TEXT("/Game/Widget/HitLevel/WBP_HitLevel.WBP_HitLevel_C"));
	if (WBP_HitLevelUIClass.Succeeded())
	{
		HitLevelUIClass = WBP_HitLevelUIClass.Class;
	}
}

void UDamageComponent::SpawnHitEffect(const FMoveDataStruct* MoveData)
{
	int32 Index = 0;
	UNiagaraComponent* HitNS = nullptr;
	for (UNiagaraComponent* Effect : HitEffectsComponents)
	{
		if (!Effect->IsActive())
		{
			HitNS = Effect;
			break;
		}
		Index++;
	}

	if (HitNS)
	{
		HitNS->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		HitNS->SetUsingAbsoluteLocation(true);
		HitNS->SetUsingAbsoluteRotation(true);
		HitNS->SetUsingAbsoluteScale(true);

		FVector Location = Me->GetMesh()->GetSocketLocation(*SocketName);
		FRotator Rotation = Me->CharacterState.AttackDirection.Rotation();
		Rotation.Pitch -= 90.0f;

		HitNS->SetWorldLocation(Location);
		HitNS->SetWorldRotation(Rotation);

		ChangeColor(HitNS, MoveData);

		HitNS->Activate();

		// 0.5초 후에 비활성화
		TWeakObjectPtr<UNiagaraComponent> WeakHitNS = HitNS;
		TWeakObjectPtr<UDamageComponent> WeakThis = this;
		GetWorld()->GetTimerManager().SetTimer(HitEffectTimers[Index], FTimerDelegate::CreateLambda([WeakThis, WeakHitNS, Index]()
		{
			UNiagaraComponent* StrongHitNS = WeakHitNS.Get();
			UDamageComponent* StrongThis = WeakThis.Get();
			if (!(StrongHitNS && StrongThis))
			{
				return;
			}
			StrongThis->ReleaseEffect(StrongHitNS, Index);
		}), 2.0f, false);
	}
}

void UDamageComponent::TakeDamage(int32 Damage)
{
	HP -= Damage;
	if (HP <= 0)
	{
		FFastLogger::LogConsole(TEXT("HP is less than 0"));
		Me->CharacterState.bKO = true;
		HP = 0;
	}

	// UI에 표시되는 HP를 업데이트
	if (MainUI)
	{
		FFastLogger::LogConsole(TEXT("UpdateHP"));
		MainUI->UpdateHP(HP, MaxHP, Me->IsLeftPlayer());
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

	for (int32 i = 0; i < MAX_NS_SIZE; i++)
	{
		UNiagaraComponent* HitNS = NewObject<UNiagaraComponent>(this, UNiagaraComponent::StaticClass());
		HitNS->SetAsset(HitEffectSystem);
		HitNS->RegisterComponent();
		HitNS->SetAutoActivate(false);
		HitNS->Deactivate();
		HitNS->SetRelativeScale3D({0.7f, 0.7f, 0.7f});
		HitEffectsComponents.Add(HitNS);
	}
	for (int32 i = 0; i < MAX_NS_SIZE; i++)
	{
		FTimerHandle Timer;
		HitEffectTimers.Add(Timer);
	}

	AMyGameMode* GameMode = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		MainUI = GameMode->GetMainUI();
	}

	for (int32 i = 0; i < MAX_HIT_LEVEL_UI; i++)
	{
		UHitLevelUI* HitLevelUI = CreateWidget<UHitLevelUI>(GetWorld(), HitLevelUIClass);
		if (HitLevelUI)
		{
			HitLevelUI->AddToViewport();
			HitLevelUI->SetVisibility(ESlateVisibility::Hidden);
			HitLevelUIs.Add(HitLevelUI);
		}
	}
	for (int32 i = 0; i < MAX_HIT_LEVEL_UI; i++)
	{
		FTimerHandle Timer;
		HitLevelUITimers.Add(Timer);
	}
}

void UDamageComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		GetWorld()->GetTimerManager().ClearTimer(HitComboResetTimer);
		for (int32 i = 0; i < MAX_NS_SIZE; i++)
		{
			GetWorld()->GetTimerManager().ClearTimer(HitEffectTimers[i]);
		}
	}
}

void UDamageComponent::ResetHitCombo()
{
	HitCombo = 0;
	// UI에 표시되는 Combo를 초기화
}

void UDamageComponent::ChangeColor(UNiagaraComponent* HitNS, const FMoveDataStruct* MoveData)
{
	if (!HitNS || !MoveData)
	{
		return;
	}

	FString HitLevel = MoveData->HitLevel.ToUpper(); // 대소문자 구분 방지
	FLinearColor NewColor;

	if (HitLevel == TEXT("HIGH"))
	{
		NewColor = FLinearColor::Red; // 높은 공격은 빨강
	}
	else if (HitLevel == TEXT("MIDDLE"))
	{
		NewColor = FLinearColor::Yellow; // 중간 공격은 노랑
	}
	else if (HitLevel == TEXT("LOW"))
	{
		NewColor = FLinearColor::Blue; // 낮은 공격은 파랑
	}
	else
	{
		NewColor = FLinearColor::White; // 기본값 (예외 처리)
	}

	// Niagara의 User Parameter 설정
	HitNS->SetNiagaraVariableLinearColor(TEXT("User.Color"), NewColor);

	// 디버깅용 로그 출력
	FFastLogger::LogConsole(TEXT("Niagara Effect Color Changed: %s"), *NewColor.ToString());

}

// SphereTrace를 활성화 하는 함수
bool UDamageComponent::DetectCollision(const FString& InSocketName)
{
	SocketName = InSocketName;
	FVector Start = Me->GetMesh()->GetSocketLocation(*SocketName);
	FVector End   = Start + (Me->GetActorForwardVector() * 100.0f);
	Start.Z += 100.0f;
	
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(Me);
	// UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, Start, SphereRadius, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResult, true);
	UKismetSystemLibrary::BoxTraceSingle(GetWorld(), Start, Start, FVector(25.0f, 25.0f, 100.0f), FRotator::ZeroRotator, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResult, true);

	if (!HitResult.bBlockingHit)
	{
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

void UDamageComponent::ReleaseEffect(UNiagaraComponent* NiagaraComponent, int32 Index)
{
	FFastLogger::LogConsole(TEXT("ReleaseEffect"));
	NiagaraComponent->Deactivate();
	
	GetWorld()->GetTimerManager().ClearTimer(HitEffectTimers[Index]);
	// 상대 좌표 모드로 복귀
	NiagaraComponent->SetUsingAbsoluteLocation(false);
	NiagaraComponent->SetUsingAbsoluteRotation(false);
	NiagaraComponent->SetUsingAbsoluteScale(false);
}

void UDamageComponent::ReleaseUI(UHitLevelUI* HitUI, int32 Index)
{
	HitUI->SetVisibility(ESlateVisibility::Hidden);
	GetWorld()->GetTimerManager().ClearTimer(HitEffectTimers[Index]);
}

void UDamageComponent::UpdateHitInfo(ABaseCharacter* Target)
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

	if (Target->CharacterState.bKO)
	{
		FFastLogger::LogConsole(TEXT("Target is already KO"));
		return;
	}

	TargetDamageComponent->TakeDamage(MoveData->Damage); // 데미지 적용
	// 아래에 계속해서 추가적인 작업을 함. (HitReaction 등) 근데 죽음 이후에 아래의 처리를 하는 것이 과연 옳을까? 근데 상관 없음
	// 왜냐하면 FSM의 우선순위를 두면 되기 때문임

	// Effect Spawn
	SpawnHitEffect(MoveData);
	// Hit Combo 처리 (UI에 표시) : 시간이 지나면 사라짐
	SpawnHitLevelUI(MoveData);
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
	Target->CharacterState.HitStun = HitEffect->StunFrames;
	// UI에 HitLevel 표시 : High, Mid, Low
	return ;
}

void UDamageComponent::SpawnHitLevelUI(const FMoveDataStruct* MoveData)
{
	int32 Index = 0;
	UHitLevelUI* HitUI = nullptr;
	for (UHitLevelUI* InHitUI : HitLevelUIs)
	{
		if (InHitUI->GetVisibility() == ESlateVisibility::Hidden)
		{
			HitUI = InHitUI;
			break;
		}
		Index++;
	}

	if (!HitUI)
	{
		return;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!PlayerController)
	{
		return;
	}

	// 소켓 위치 -> 화면 좌표 변환
	FVector WorldLocation = Me->GetMesh()->GetSocketLocation(*SocketName);
	FVector2D ScreenPosition;
	bool bProjected = PlayerController->ProjectWorldLocationToScreen(WorldLocation, ScreenPosition, true);
	if (!bProjected)
	{
		return;
	}

	// 화면 크기 가져오기
	int32 ScreenWidth = 0;
	int32 ScreenHeight = 0;
	PlayerController->GetViewportSize(ScreenWidth, ScreenHeight);
	FFastLogger::LogScreen(FColor::Red, TEXT("ScreenSize: %d, %d"), ScreenWidth, ScreenHeight);
	FFastLogger::LogScreen(FColor::Green, TEXT("ScreenPosition: %f, %f"), ScreenPosition.X, ScreenPosition.Y);
	FFastLogger::LogScreen(FColor::Cyan, TEXT("WorldLocation: %f, %f, %f"), WorldLocation.X, WorldLocation.Y, WorldLocation.Z);

	// 중앙 정렬(위젯의 중앙이 좌표에 맞춰짐)
	// HitUI->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));

	// 화면 범위 안에 있는지 체크
	if (ScreenPosition.X < 0 || ScreenPosition.X > ScreenWidth ||
		ScreenPosition.Y < 0 || ScreenPosition.Y > ScreenHeight)
	{
		// 화면 밖이면 숨기고 종료 (원한다면 그냥 숨기기만 하고 return 안 해도 됨)
		HitUI->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	// **중앙 정렬**이므로, 오프셋 없이 SetPositionInViewport를 한 번만 호출
	HitUI->SetPositionInViewport(ScreenPosition, true);

	// HitLevel 설정
	HitUI->SetHitLevel(MoveData->HitLevel.ToUpper());

	// 화면에 표시
	HitUI->SetVisibility(ESlateVisibility::Visible);

	// 일정 시간 후 UI 숨기기(0.4초 예시)
	TWeakObjectPtr<UHitLevelUI> WeakHitLevelUI = HitUI;
	TWeakObjectPtr<UDamageComponent> WeakThis = this;
	GetWorld()->GetTimerManager().SetTimer(
		HitLevelUITimers[Index],
		FTimerDelegate::CreateLambda([WeakThis, WeakHitLevelUI, Index]()
		{
			UHitLevelUI* StrongHitUI = WeakHitLevelUI.Get();
			UDamageComponent* StrongThis = WeakThis.Get();
			if (!(StrongHitUI && StrongThis))
			{
				return;
			}
			StrongThis->ReleaseUI(StrongHitUI, Index);
		}),
		0.4f,
		false
	);

}
