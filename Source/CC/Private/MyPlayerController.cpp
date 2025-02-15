#include "MyPlayerController.h"

#include "FastLogger.h"
#include "Hwoarang.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Pawn.h"

AMyPlayerController::AMyPlayerController()
{
    //화랑 입력
    ConstructorHelpers::FObjectFinder<UInputMappingContext> TempIMCHwoarang(TEXT("/Game/Inputs/IMC_Hwoarang.IMC_Hwoarang"));
    if (TempIMCHwoarang.Succeeded())
    {
        IMC_Hwoarang = TempIMCHwoarang.Object;
    }
    
    ConstructorHelpers::FObjectFinder<UInputAction> TempIALeftHwoarang(TEXT("/Game/Inputs/IA_MoveLeft_Hwoarang.IA_MoveLeft_Hwoarang"));
    if (TempIALeftHwoarang.Succeeded())
    {
        IA_MoveLeft_Hwoarang = TempIALeftHwoarang.Object;
    }
    ConstructorHelpers::FObjectFinder<UInputAction> TempIARightHwoarang(TEXT("/Game/Inputs/IA_MoveRight_Hwoarang.IA_MoveRight_Hwoarang"));
    if (TempIARightHwoarang.Succeeded())
    {
        IA_MoveRight_Hwoarang = TempIARightHwoarang.Object;
    }
    ConstructorHelpers::FObjectFinder<UInputAction> TempIAJumpHwoarang(TEXT("/Game/Inputs/IA_Jump_Hwoarang.IA_Jump_Hwoarang"));
    if (TempIAJumpHwoarang.Succeeded())
    {
        IA_Jump_Hwoarang = TempIAJumpHwoarang.Object;
    }
    //스티브폭스 입력
    ConstructorHelpers::FObjectFinder<UInputMappingContext> TempIMCSteveFox(TEXT("/Game/Inputs/IMC_SteveFox.IMC_SteveFox"));
    if (TempIMCSteveFox.Succeeded())
    {
        IMC_SteveFox = TempIMCSteveFox.Object;
    }
    
    ConstructorHelpers::FObjectFinder<UInputAction> TempIALeftSteveFox(TEXT("/Game/Inputs/IA_MoveLeft_SteveFox.IA_MoveLeft_SteveFox"));
    if (TempIALeftSteveFox.Succeeded())
    {
        IA_MoveLeft_SteveFox = TempIALeftSteveFox.Object;
    }
    ConstructorHelpers::FObjectFinder<UInputAction> TempIARightSteveFox(TEXT("/Game/Inputs/IA_MoveRight_SteveFox.IA_MoveRight_SteveFox"));
    if (TempIARightSteveFox.Succeeded())
    {
        IA_MoveRight_SteveFox = TempIARightSteveFox.Object;
    }
    ConstructorHelpers::FObjectFinder<UInputAction> TempIAJumpSteveFox(TEXT("/Game/Inputs/IA_Jump_SteveFox.IA_Jump_SteveFox"));
    if (TempIAJumpSteveFox.Succeeded())
    {
        IA_Jump_SteveFox = TempIAJumpSteveFox.Object;
    }
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
        	if (IMC_Hwoarang)
        	{
        		Subsystem->AddMappingContext(IMC_Hwoarang, 0);
        	}
            if (IMC_SteveFox)
            {
                Subsystem->AddMappingContext(IMC_SteveFox, 0);
            }
        }
    }
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // 화랑 입력 바인딩
        if (IA_MoveLeft_Hwoarang)
        {
            EnhancedInput->BindAction(IA_MoveLeft_Hwoarang, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMoveLeftHwoarang);
        }
        if (IA_MoveRight_Hwoarang)
        {
           
            EnhancedInput->BindAction(IA_MoveRight_Hwoarang, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMoveRightHwoarang);
        }
        if (IA_Jump_Hwoarang)
        {
           
            EnhancedInput->BindAction(IA_Jump_Hwoarang, ETriggerEvent::Triggered, this, &AMyPlayerController::OnJumpHwoarang);
        }

        // 스티브폭스 입력 바인딩
        if (IA_MoveLeft_SteveFox)
        {
            EnhancedInput->BindAction(IA_MoveLeft_SteveFox, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMoveLeftSteveFox);
        }
        if (IA_MoveRight_SteveFox)
        {
           
            EnhancedInput->BindAction(IA_MoveRight_SteveFox, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMoveRightSteveFox);
        }
        if (IA_Jump_SteveFox)
        {
           
            EnhancedInput->BindAction(IA_Jump_SteveFox, ETriggerEvent::Triggered, this, &AMyPlayerController::OnJumpSteveFox);
        }
    }
}

void AMyPlayerController::RegisterPlayers(ACharacter* InPlayer1, ACharacter* InPlayer2)
{
        Player1 = InPlayer1;
        Player2 = InPlayer2;
}


//화랑 입력 함수
void AMyPlayerController::OnMoveRightHwoarang(const FInputActionValue& Value)
{
    float ActionValue = Value.Get<float>();

    if (Player1 != nullptr)
    {
        FVector Direction = Player1->GetActorRightVector() ;
        //FFastLogger::LogScreen(FColor::Red, TEXT("Move Left : %f"), ActionValue);
        Player1->AddMovementInput(Direction, ActionValue);
    }
}

void AMyPlayerController::OnMoveLeftHwoarang(const FInputActionValue& Value)
{
    float ActionValue = Value.Get<float>();

    if (Player1 != nullptr)
    {
        FVector Direction = FVector::RightVector * -1;
        Player1->AddMovementInput(Direction);
    }
}

void AMyPlayerController::OnJumpHwoarang(const FInputActionValue& Value)
{
    if (ACharacter* MyCharacter = Cast<ACharacter>(Player1))
    {
        Player1->Jump();
    }
}

//스티브폭스 입력 함수
void AMyPlayerController::OnMoveRightSteveFox(const FInputActionValue& Value)
{
    float ActionValue = Value.Get<float>();

    if (Player2 != nullptr)
    {
        FVector Direction = Player2->GetActorRightVector();
        Player2->AddMovementInput(Direction, ActionValue);
    }
}

void AMyPlayerController::OnMoveLeftSteveFox(const FInputActionValue& Value)
{
    float ActionValue = Value.Get<float>();

    if (Player2 != nullptr)
    {
        FVector Direction = FVector::RightVector * -1 ;
        Player2->AddMovementInput(Direction);
    }
}

void AMyPlayerController::OnJumpSteveFox(const FInputActionValue& Value)
{
    if (ACharacter* MyCharacter = Cast<ACharacter>(Player2))
    {
        Player2->Jump();
    }
}


