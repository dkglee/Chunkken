#include "HwoarangAnimInstance.h"

UHwoarangAnimInstance::UHwoarangAnimInstance()
{
	// Base Montages
	static ConstructorHelpers::FObjectFinder<UAnimMontage> IdleMontage
	(TEXT("/Game/Animations/Montages/Tekken_Idle_Montage.Tekken_Idle_Montage"));
	if (IdleMontage.Succeeded())
	{
		MontageMap.Add(TEXT("IDLE"), IdleMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MoveForwardMontage
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_MOVE_FORWARD_Montage.HWR_Tekken_MOVE_FORWARD_Montage"));
	if (MoveForwardMontage.Succeeded())
	{
		MontageMap.Add(TEXT("MOVE_FORWARD"), MoveForwardMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MoveBackwardMontage
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_MOVE_BACK_Montage.HWR_Tekken_MOVE_BACK_Montage"));
	if (MoveBackwardMontage.Succeeded())
	{
		MontageMap.Add(TEXT("MOVE_BACKWARD"), MoveBackwardMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> JumpMontage
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_Jump_Montage.HWR_Tekken_Jump_Montage"));
	if (JumpMontage.Succeeded())
	{
		MontageMap.Add(TEXT("JUMP"), JumpMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HeadHitLeft
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_Head_Hit_Left_Montage.HWR_Tekken_Head_Hit_Left_Montage"));
	if (HeadHitLeft.Succeeded())
	{
		MontageMap.Add(TEXT("HeadHitLeft"), HeadHitLeft.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HeadHitRight
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_Head_Hit_Right_Montage.HWR_Tekken_Head_Hit_Right_Montage"));
	if (HeadHitRight.Succeeded())
	{
		MontageMap.Add(TEXT("HeadHitRight"), HeadHitRight.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BodyHitLeft
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_Hit_Body_Left_Montage.HWR_Tekken_Hit_Body_Left_Montage"));
	if (BodyHitLeft.Succeeded())
	{
		MontageMap.Add(TEXT("BodyHitLeft"), BodyHitLeft.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BodyHitRight
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_Hit_Body_Right_Montage.HWR_Tekken_Hit_Body_Right_Montage"));
	if (BodyHitRight.Succeeded())
	{
		MontageMap.Add(TEXT("BodyHitRight"), BodyHitRight.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AirBornMontage
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_Hit_Airborne.HWR_Tekken_Hit_Airborne"));
	if (AirBornMontage.Succeeded())
	{
		MontageMap.Add(TEXT("AirBorn"), AirBornMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> GetupMontage
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_Get_Up_Seq_Montage.HWR_Tekken_Get_Up_Seq_Montage"));
	if (GetupMontage.Succeeded())
	{
		MontageMap.Add(TEXT("GetUp"), GetupMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> KOAnimation
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_Hit_Death_Seq_Montage.HWR_Tekken_Hit_Death_Seq_Montage"));
	if (KOAnimation.Succeeded())
	{
		MontageMap.Add(TEXT("KO"), KOAnimation.Object);
	}

	// Hwoarang Montages
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RightKickMontage
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_Mma_Kick_Montage.HWR_Tekken_Mma_Kick_Montage"));
	if (RightKickMontage.Succeeded())
	{
		MontageMap.Add(TEXT("RightKick"), RightKickMontage.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RightKickMontage2
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_WHEEL_KICK_Montage.HWR_Tekken_WHEEL_KICK_Montage"));
	if (RightKickMontage2.Succeeded())
	{
		MontageMap.Add(TEXT("RightKick2"), RightKickMontage2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RightKickMontage3
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Tekken_540_kick_ROOT_MOTION_Montage.HWR_Tekken_540_kick_ROOT_MOTION_Montage"));
	if (RightKickMontage3.Succeeded())
	{
		MontageMap.Add(TEXT("RightKick3"), RightKickMontage3.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RightKickMontage4
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Frank_FS3_Kick08_Montage.HWR_Frank_FS3_Kick08_Montage"));
	if (RightKickMontage4.Succeeded())
	{
		MontageMap.Add(TEXT("RightKick4"), RightKickMontage4.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LeftKickMontage
	(TEXT("/Game/Animations/Montages/Hwoarang/HWR_Mma_KickL_Montage.HWR_Mma_KickL_Montage"));
	if (LeftKickMontage.Succeeded())
	{
		MontageMap.Add(TEXT("LeftKick"), LeftKickMontage.Object);
	}
}
