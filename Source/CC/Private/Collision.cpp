// #include "Collision.h"
// #include "CC/Public/Collision.h"
//
// #include "BaseCharacter.h"
// #include "Damage.h"
// #include "HitEffectParser.h"
// #include "MoveDataStruct.h"
// #include "MoveParser.h"
// #include "Components/BoxComponent.h"
// #include "GameFramework/Character.h"
//
// #include "Engine/DataTable.h"
// #include "Engine/OverlapResult.h"
//
// UCollision::UCollision()
// {
//     PrimaryComponentTick.bCanEverTick = false;
//     bAttackActive = false;
// }
//
// void UCollision::BeginPlay()
// {
//     Super::BeginPlay();
//
// }
//
//  
// bool UCollision::CheckCollision(ACharacter* Attacker, ACharacter* Defender, int32 MoveID)
// {
//     if (!bAttackActive || !Attacker || !Defender)
//     {
//         UE_LOG(LogTemp, Warning, TEXT("충돌검사 - 공격자와 피격자 동일"));
//         return false;
//     }
//
//     ABaseCharacter* AttackerCharacter = Cast<ABaseCharacter>(Attacker);
//     ABaseCharacter* DefenderCharacter = Cast<ABaseCharacter>(Defender);
//     
//     if (!bAttackActive || !DefenderCharacter )
//     {
//         UE_LOG(LogTemp, Warning, TEXT("충돌검사 - 캐릭터 또는 데이터테이블 찾지못함"));
//         return false;
//     }
//
//     int32 HitData = UHitEffectParser::GetHitEffectByMoveID(MoveID);
//     const FHitEffectStruct* Hitdatas= UHitEffectParser::GetHitEffect(HitData);
//     if (!Hitdatas)
//     {
//         UE_LOG(LogTemp, Warning, TEXT("충돌검사 - 데이터테이블에서 MoveID를 찾지못함"));
//         return false;
//     }
//
//     const FMoveDataStruct* MoveDataStruct = UMoveParser::GetMoveDataByMoveID(MoveID);
//     if (!MoveDataStruct)
//     {
//         return false;   
//     }
//     int32 AttackerActiveFrame = MoveDataStruct->ActiveFrames;
//     int32 AttackerStartUp = MoveDataStruct->StartUp;
//     int32 AttackerRecovery = MoveDataStruct->Recovery;
//
//     //ActiveFrame에서만 충돌판정
//     if (AttackerCharacter->NewFrameIndex <AttackerStartUp || AttackerCharacter->NewFrameIndex >(AttackerStartUp+AttackerActiveFrame))
//     {
//         UE_LOG(LogTemp, Warning, TEXT("충돌검사 -  MoveID %d 공격이 ActiveFrame 범위를 벗어났습니다. 현재 프레임: %d"),MoveID, AttackerCharacter->NewFrameIndex);
//         
//         return false;
//     }
//     //hitbox 한 번에 검사
//         
//     for (UBoxComponent* HitBox : AttackerCharacter->CollisionComponent->HitBoxes)
//     {
//         if (!HitBox) continue;
//
//         // 충돌된 객체 리스트
//         TArray<FOverlapResult> Overlaps;
//
//         // 충돌된 모든 객체를 한 번에 검색
//         FCollisionShape CollisionShape = FCollisionShape::MakeBox(HitBox->GetUnscaledBoxExtent());
//         FCollisionQueryParams QueryParams;
//         QueryParams.AddIgnoredActor(Attacker);  // 자기 자신은 제외
//
//         bool bOverlapDetected = GetWorld()->OverlapMultiByChannel(
//             Overlaps,
//             HitBox->GetComponentLocation(),
//             FQuat::Identity,
//             ECollisionChannel::ECC_Pawn,  // 캐릭터만 충돌 검사
//             CollisionShape,
//             QueryParams
//         );
//
//         if (bOverlapDetected)
//         {
//             for (const FOverlapResult& Overlap : Overlaps)
//             {
//                 ACharacter* OverlappedCharacter = Cast<ACharacter>(Overlap.GetActor());
//
//                 //  방어자와 충돌했는지 확인
//                 if (OverlappedCharacter == Defender)
//                 {
//                     UE_LOG(LogTemp, Log, TEXT("충돌 성공- %s 가(이) %s 에게 MoveID %d 공격 적중!"),
//                         *AttackerCharacter->GetName(), *DefenderCharacter->GetName(), MoveID);
//
//                     UDamage* DamageComponent = AttackerCharacter->FindComponentByClass<UDamage>();
//                     if (DamageComponent)
//                     {
//                         DamageComponent->ApplyDamage(Attacker, Defender, MoveID);
//                         UE_LOG(LogTemp, Log, TEXT("데미지 적용- %s 에게 데미지 적용 완료"), *DefenderCharacter->GetName());
//                     }
//                     return true;
//                 }
//             }
//         }
//     }
//     UE_LOG(LogTemp, Warning, TEXT("충돌검사 - 충돌없음"))
//         return false;
//     
// }
