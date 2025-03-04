#include "Hwoarang.h"

#include "FastLogger.h"
#include "TekkenAnimIntance.h"

// Sets default values
AHwoarang::AHwoarang()
{
	CharID = 102;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_HWR
	(TEXT("/Game/Characters/Hwoarang/Taunt.Taunt"));
	if (SKM_HWR.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SKM_HWR.Object);
	}
	
	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_HWR
	(TEXT("/Game/Animations/ABP_HwoarangAnimInstance.ABP_HwoarangAnimInstance_C"));
	if (ABP_HWR.Succeeded())
	{
		TekkenAnimClass = ABP_HWR.Class;
	}

	GetMesh()->SetAnimInstanceClass(TekkenAnimClass);
	
	GetMesh()->SetRelativeLocation({0, 0, -90});
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

// Called when the game starts or when spawned
void AHwoarang::BeginPlay()
{
	Super::BeginPlay();
	
}

