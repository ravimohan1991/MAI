// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#include "MAIController.h"
#include "MAIBrainComponent.h"
#include "Vector.h"
#include "Engine/World.h"

AMAIController::AMAIController()
{
    // for Tick purpose. Try ticking the brain instead.
    PrimaryActorTick.bCanEverTick = true;
}

void AMAIController::BeginPlay()
{
   // UMAIBrainComponent BrainComponent(this);
    PrimaryActorTick.bCanEverTick = true;
    UE_LOG(LogTemp, Warning, TEXT("Beginplay of MAIController"));
    Super::BeginPlay();
}

void AMAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    //UE_LOG(LogTemp, Warning, TEXT("Tick is working."));
    UE_LOG(LogTemp, Warning, TEXT("Closest box is %s."), *FindClosestBox()->GetActorLocation().ToString());

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
