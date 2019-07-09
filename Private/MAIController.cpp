// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#include "MAIController.h"
#include "MAIBrainComponent.h"
#include "Vector.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "EngineUtils.h"

AMAIController::AMAIController()
{
    // for Tick purpose.
    PrimaryActorTick.bCanEverTick = false;
}

void AMAIController::BeginPlay()
{
    BrainComponent = NewObject<UMAIBrainComponent>(this);
    BrainComponent->RegisterComponent();
    Super::BeginPlay();
}

void AMAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
   // AStaticMeshActor* closest = FindClosestBox();
   // UE_LOG(LogTemp, Warning, TEXT("Closest box is %s at distance of %d."), *closest->GetName(), int32((closest->GetActorLocation() - MAIGameRep->GetSelfLocation()).Size()));

}

AStaticMeshActor* AMAIController::FindClosestBox()
{
    float Distance = 999999;
    AStaticMeshActor* closest;
    for( auto& Box : MAIGameRep->GetWhiteBoxes() )
    {
        FVector diffv = MAIGameRep->GetSelfLocation() - ((AStaticMeshActor*) Box)->GetActorLocation();
        float diff = diffv.Size();
        if( diff < Distance)
        {
            closest = (AStaticMeshActor*) Box;
            Distance = diff;
        }
    }
    return closest;
}

APawn* AMAIController::FindDummy()
{
    FString MeshRecognition(TEXT("Dummy"));
    FString Left(TEXT("l"));
    FString Right(TEXT("r"));

    for( TActorIterator<APawn> ActorItr(GetWorld()); ActorItr; ++ActorItr )
    {
        FString tempst(*ActorItr->GetName());
        if(tempst.Split(*MeshRecognition, &Left, &Right))
        {
           UE_LOG(LogTemp, Warning, TEXT("Goccha"), *ActorItr->GetName());
           return  *ActorItr;
        }

    }
    return nullptr;
}


void AMAIController::StartPossessing(APawn *PPawn)
{
    OnPossess(PPawn);
}
