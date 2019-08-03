// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#include "MAI/Public/MAIController/MAIController.h"
#include "MAI/Public/MAIBrainComponent.h"
#include "Vector.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "EngineUtils.h"
#include "MAI/Public/Blackboard/MAIBlackboardComponent.h"
#include "MAI/Public/Blackboard/BlackboardKeyType_TMap.h"

AMAIController::AMAIController()
{
    // for Tick purpose.
    PrimaryActorTick.bCanEverTick = false;
}

void AMAIController::BeginPlay()
{
    /*BrainComponent = NewObject<UMAIBrainComponent>(this);
    BrainComponent->RegisterComponent();*/

    Super::BeginPlay();
}

void AMAIController::SetGameRep(AMAIGameState *GR)
{
    MAIGameRep = GR;

    // setup blackboard component
    if(!MAIGameRep->GetBlackBoard())
    {
        UMAIBlackboardComponent* BB =  NewObject<UMAIBlackboardComponent>(this, TEXT("BlackboardComponent"));
        if(BB)
        {
            BB->RegisterComponent();
            MAIGameRep->SetBlackBoard(BB);

            UBlackboardData* BlackboardAsset = NewObject<UBlackboardData>(BB);
            //BlackboardAsset->UpdatePersistentKey<UBlackboardKeyType_TMap>(FName("PlayerScore"));
            BB->InitializeBlackboard(*BlackboardAsset);
        }
    }

}

void AMAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AMAIController::StartPossessing(APawn *PPawn)
{
    OnPossess(PPawn);
}

bool AMAIController::LineOfSightTo(const AActor *Other, FVector ViewPoint, bool bAlternateChecks) const
{
    return Super::LineOfSightTo(Other, ViewPoint, bAlternateChecks);
}
