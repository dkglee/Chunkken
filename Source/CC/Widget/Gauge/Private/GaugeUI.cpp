// Fill out your copyright notice in the Description page of Project Settings.


#include "GaugeUI.h"

#include "Components/ProgressBar.h"

void UGaugeUI::UpdateHP(int32 HP, int32 MaxHP)
{
	// HP 게이지 업데이트
	float Percent = (float)HP / (float)MaxHP;
	Percent = 1.0f - Percent; // HP가 감소하는 방향으로 설정
	RedBar->SetPercent(Percent);

	// 0.5초 후에 BlackBar 감소 시작
	TWeakObjectPtr<UGaugeUI> WeakThis = this;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([WeakThis, Percent]()
	{
		UGaugeUI* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		// 목표 BlackBar 퍼센트 설정
		StrongThis->TargetBlackBarPercent = Percent;
		StrongThis->bShouldUpdateBlackBar = true;

	}), 0.5f, false);
}

void UGaugeUI::UpdateBlackHP(float Percent)
{
	// BlackBar를 즉시 업데이트하는 경우
	BlackBar->SetPercent(Percent);
}

// Tick을 활용한 Interpolation
void UGaugeUI::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	// Interpolation 활성화 시
	if (bShouldUpdateBlackBar)
	{
		// 보간을 통해 BlackBar의 값 점진적 감소
		float CurrentPercent = BlackBar->GetPercent();
		float NewPercent = FMath::FInterpTo(CurrentPercent, TargetBlackBarPercent, DeltaTime, 2.0f); // 보간 속도 = 2.0f (조절 가능)

		// 업데이트
		BlackBar->SetPercent(NewPercent);

		// 목표 값에 도달하면 보간 종료
		if (FMath::IsNearlyEqual(NewPercent, TargetBlackBarPercent, 0.01f))
		{
			bShouldUpdateBlackBar = false;
			BlackBar->SetPercent(TargetBlackBarPercent);
		}
	}
}

void UGaugeUI::NativeDestruct()
{
	Super::NativeDestruct();

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
