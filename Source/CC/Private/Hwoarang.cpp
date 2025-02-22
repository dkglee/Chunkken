#include "Hwoarang.h"

#include "Components/BoxComponent.h"


// Sets default values
AHwoarang::AHwoarang()
{
	CharID = 102;

	GetMesh()->SetRelativeLocation({0, 0, -90});
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

// Called when the game starts or when spawned
void AHwoarang::BeginPlay()
{
	Super::BeginPlay();
	
}

