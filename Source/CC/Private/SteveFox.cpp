#include "SteveFox.h"
#include "TekkenAnimIntance.h"

// Sets default values
ASteveFox::ASteveFox()
{
	CharID = 101;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_Steve
	(TEXT("/Game/Characters/Steve/Defeated.Defeated"));
	if (SKM_Steve.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SKM_Steve.Object);
	}
	
	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_Steve
	(TEXT("/Game/Animations/ABP_SteveAnimInstance.ABP_SteveAnimInstance_C"));
	if (ABP_Steve.Succeeded())
	{
		TekkenAnimClass = ABP_Steve.Class;
	}

	GetMesh()->SetAnimInstanceClass(TekkenAnimClass);
	
	GetMesh()->SetRelativeLocation({0, 0, -90});
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

// Called when the game starts or when spawned
void ASteveFox::BeginPlay()
{
	Super::BeginPlay();
}
