#include "Hwoarang.h"

AHwoarang::AHwoarang()
{
	AutoPossessPlayer = EAutoReceiveInput::Disabled;

	CharID = 102;
}

// Called when the game starts or when spawned
void AHwoarang::BeginPlay()
{
	Super::BeginPlay();
	
}
