// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#include "MAIBrainComponent.h"
#include "MAIController.h"

UMAIBrainComponent::UMAIBrainComponent()
{
    PrimaryComponentTick.bCanEverTick = false;//Disabling tick for now
    bTickInEditor = true;
}

void UMAIBrainComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
   // UE_LOG(LogTemp, Warning, TEXT("Brain Ticking! AI owner is %s"), *AIOwner->GetName());
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    /*if(bShouldExplore)
    {*/
        //UE_LOG(LogTemp, Warning, TEXT("Behavior mode: Exploring by spinning..."));
        //FRotator temp = AIOwner->GetPawn()->GetActorRotation();
        //const FRotator resultRotation = FMath::RInterpTo( temp, temp + FRotator(0, 10, 0), DeltaTime, 2.0 );
       // ((AMAIController*) AIOwner)->FindDummy()->SetActorRotation(resultRotation);
        //((AMAIController*) AIOwner)->FindDummy()->GetController()->SetControlRotation(resultRotation);

        // let the viewpoint spin along
        ((AMAIController*) AIOwner)->GetGameRep()->GetCameraManager()->SetViewTarget(AIOwner->GetPawn());//((AMAIController*) AIOwner)->FindDummy());

        // see if any of the white box is at lineofsight. If yes, add it to seen white box
        CheckForLOSBoxes();
        AStaticMeshActor* closest = FindClosestBox(((AMAIController*) AIOwner)->GetGameRep()->GetWhiteBoxes());//GetSeenWhiteBoxes());

        FRotator InitialRot = AIOwner->GetPawn()->GetActorRotation();//GetViewRotation();//GetActorRotation();
        //FVector InitialVec = InitialRot.Vector();
        FVector FinalVec = (closest->GetActorLocation() - AIOwner->GetPawn()->GetActorLocation());
        FRotator FinalRotation = FinalVec.Rotation() - InitialRot;
        const FRotator resultRotation = FMath::RInterpTo(InitialRot, FinalRotation, DeltaTime, 2.0);
        ((AMAIController*) AIOwner)->FindDummy()->SetActorRotation(resultRotation);
    /*}*/
}

void UMAIBrainComponent::CheckForLOSBoxes()
{
    for(auto& Box : ((AMAIController*) AIOwner)->GetGameRep()->GetWhiteBoxes())
    {
        if(AIOwner->LineOfSightTo(Box, FVector(0, 0, 0)))
        {
            ((AMAIController*) AIOwner)->GetGameRep()->AddSeenWhiteBoxes(Box);
        }
        else
        {
            ((AMAIController*) AIOwner)->GetGameRep()->RemoveSeenWhiteBoxes(Box);
        }
    }
}

AStaticMeshActor* UMAIBrainComponent::FindClosestBox(TArray<AStaticMeshActor*> ASMArray)
{
    float Distance = 999999;
    AStaticMeshActor* closest;
    for( auto& Box : ASMArray )
    {
        FVector diffv = AIOwner->GetPawn()->GetActorLocation() - ((AStaticMeshActor*) Box)->GetActorLocation();
        float diff = diffv.Size();
        if( diff < Distance)
        {
            closest = (AStaticMeshActor*) Box;
            Distance = diff;
        }
    }
    return closest;
}
