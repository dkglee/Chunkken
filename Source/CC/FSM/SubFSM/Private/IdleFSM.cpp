#include "IdleFSM.h"

#include "BaseCharacter.h"
#include "FastLogger.h"

FString UIdleFSM::StateName = TEXT("STANDING_IDLE");

void UIdleFSM::Enter(int32 ChildID)
{
	Super::Enter(ChildID);
	
	Me->CharacterState.bAttackAvailable = true;
}

void UIdleFSM::Update()
{
	Super::Update();
}

void UIdleFSM::Exit()
{
	Super::Exit();
}

FString UIdleFSM::GetStateName()
{
	return StateName;
}
