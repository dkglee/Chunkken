#include "SteveAnimInstance.h"

USteveAnimInstance::USteveAnimInstance()
{
	// Base Montages
	static ConstructorHelpers::FObjectFinder<UAnimMontage> IdleMontage
	(TEXT("/Game/Animations/Montages/Tekken_Idle_Montage.Tekken_Idle_Montage"));
	if (IdleMontage.Succeeded())
	{
		MontageMap.Add(TEXT("IDLE"), IdleMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MoveForwardMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_MOVE_FORWARD_Montage.STV_Tekken_MOVE_FORWARD_Montage"));
	if (MoveForwardMontage.Succeeded())
	{
		MontageMap.Add(TEXT("MOVE_FORWARD"), MoveForwardMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MoveBackwardMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_MOVE_BACK_Montage.STV_Tekken_MOVE_BACK_Montage"));
	if (MoveBackwardMontage.Succeeded())
	{
		MontageMap.Add(TEXT("MOVE_BACKWARD"), MoveBackwardMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> JumpMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_Jump_Montage.STV_Tekken_Jump_Montage"));
	if (JumpMontage.Succeeded())
	{
		MontageMap.Add(TEXT("JUMP"), JumpMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HeadHitLeft
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_Head_Hit_Left_Montage.STV_Tekken_Head_Hit_Left_Montage"));
	if (HeadHitLeft.Succeeded())
	{
		MontageMap.Add(TEXT("HeadHitLeft"), HeadHitLeft.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HeadHitRight
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_Head_Hit_Right_Montage.STV_Tekken_Head_Hit_Right_Montage"));
	if (HeadHitRight.Succeeded())
	{
		MontageMap.Add(TEXT("HeadHitRight"), HeadHitRight.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BodyHitLeft
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_Hit_Body_Left_Montage.STV_Tekken_Hit_Body_Left_Montage"));
	if (BodyHitLeft.Succeeded())
	{
		MontageMap.Add(TEXT("BodyHitLeft"), BodyHitLeft.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BodyHitRight
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_Hit_Body_Right_Montage.STV_Tekken_Hit_Body_Right_Montage"));
	if (BodyHitRight.Succeeded())
	{
		MontageMap.Add(TEXT("BodyHitRight"), BodyHitRight.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AirBornMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_HWR_Tekken_Hit_Airborne.STV_HWR_Tekken_Hit_Airborne"));
	if (AirBornMontage.Succeeded())
	{
		MontageMap.Add(TEXT("AirBorn"), AirBornMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> GetupMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_Get_Up_Seq_Montage.STV_Tekken_Get_Up_Seq_Montage"));
	if (GetupMontage.Succeeded())
	{
		MontageMap.Add(TEXT("GetUp"), GetupMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> KOAnimation
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_Hit_Death_Seq_Montage.STV_Tekken_Hit_Death_Seq_Montage"));
	if (KOAnimation.Succeeded())
	{
		MontageMap.Add(TEXT("KO"), KOAnimation.Object);
	}

	// Steve Montages
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SteveLeftPunchMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_Left_Punch_Montage.STV_Tekken_Left_Punch_Montage"));
	if (SteveLeftPunchMontage.Succeeded())
	{
		MontageMap.Add(TEXT("Jab"), SteveLeftPunchMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SteveRightPunchMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_RightPunch_Montage.STV_Tekken_RightPunch_Montage"));
	if (SteveRightPunchMontage.Succeeded())
	{
		MontageMap.Add(TEXT("RightJab"), SteveRightPunchMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SteveVanguardMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_Hook_Montage.STV_Tekken_Hook_Montage"));
	if (SteveVanguardMontage.Succeeded())
	{
		MontageMap.Add(TEXT("VanguardRush1"), SteveVanguardMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SteveDuckingBodyBlow
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_RightHook_Montage.STV_Tekken_RightHook_Montage"));
	if (SteveDuckingBodyBlow.Succeeded())
	{
		MontageMap.Add(TEXT("DuckingBodyBlow"), SteveDuckingBodyBlow.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ConquerorCombo1
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_ConquerorComb1_Montage.STV_Tekken_ConquerorComb1_Montage"));
	if (ConquerorCombo1.Succeeded())
	{
		MontageMap.Add(TEXT("ConquerorCombo1"), ConquerorCombo1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ConquerorComboRightHook1
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_ConquerorCombHook_Montage.STV_Tekken_ConquerorCombHook_Montage"));
	if (ConquerorComboRightHook1.Succeeded())
	{
		MontageMap.Add(TEXT("ConquerorComboRightHook1"), ConquerorComboRightHook1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> UppercutMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_Uppercut_Montage.STV_Uppercut_Montage"));
	if (UppercutMontage.Succeeded())
	{
		MontageMap.Add(TEXT("Uppercut"), UppercutMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SteveBurstHammerMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_Frank_FS2_Punch_PowerSmash_Inplace_Montage.STV_Frank_FS2_Punch_PowerSmash_Inplace_Montage"));
	if (SteveBurstHammerMontage.Succeeded())
	{
		MontageMap.Add(TEXT("BurstHammer"), SteveBurstHammerMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> CrescentHookMontage 
	(TEXT("/Game/Animations/Montages/Steve/STV_Frank_FS2_Punch_Right_UpperCut_Inplace_Montage.STV_Frank_FS2_Punch_Right_UpperCut_Inplace_Montage"));
	if (CrescentHookMontage.Succeeded())
	{
		MontageMap.Add(TEXT("CrescentHook"), CrescentHookMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> WildmanMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_Tekken_ConquerorComb1_Montage.STV_Tekken_ConquerorComb1_Montage"));
	if (WildmanMontage.Succeeded())
	{
		MontageMap.Add(TEXT("WildmanCombo1"), WildmanMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> QuickHookMontage
	(TEXT("/Game/Animations/Montages/Steve/STV_Frank_FS3_Punch03_Montage.STV_Frank_FS3_Punch03_Montage"));
	if (QuickHookMontage.Succeeded())
	{
		MontageMap.Add(TEXT("QuickHook"), QuickHookMontage.Object);
	}
}
