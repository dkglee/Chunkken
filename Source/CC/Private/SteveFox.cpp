#include "SteveFox.h"

ASteveFox::ASteveFox()
{
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	
	CharID = 101;
}

// Called when the game starts or when spawned
void ASteveFox::BeginPlay()
{
	Super::BeginPlay();
	
}
