// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#include "MAIBrainComponent.h"
#include "MAIController.h"

UMAIBrainComponent::UMAIBrainComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bTickInEditor = true;
}

void UMAIBrainComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
   // UE_LOG(LogTemp, Warning, TEXT("Brain Ticking! AI owner is %s"), *AIOwner->GetName());
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(/*bShouldExplore*/ AIOwner->GetPawn())
    {
        //UE_LOG(LogTemp, Warning, TEXT("MAI Activated"));

        // see if any of the white box is at lineofsight. If yes, add it to seen white box
        //CheckForLOSBoxes();
        AStaticMeshActor* closest = FindClosestBox(((AMAIController*) AIOwner)->GetGameRep()->GetWhiteBoxes());//GetSeenWhiteBoxes());

        FRotator InitialRot = AIOwner->GetControlRotation();
        FVector InitialVec = InitialRot.Vector();
        FVector FinalVec = closest->GetActorLocation() - GetAbsMuzzleVec(InitialRot);

        // UE_LOG(LogTemp, Warning, TEXT("The FinalVec is %s"), *FinalVec.ToString());
        FRotator FinalRotation = FinalVec.Rotation();
        const FRotator resultRotation = FMath::RInterpTo(InitialRot, FinalRotation, DeltaTime, 2.0);
        //  UE_LOG(LogTemp, Warning, TEXT("The resultRotation is %s"), *resultRotation.ToString());
        AIOwner->SetControlRotation(resultRotation);
        UE_LOG(LogTemp, Warning, TEXT("resultRotation is %s"), *resultRotation.ToString());
        AIOwner->GetPawn()->SetActorRotation(resultRotation);//  SetControlRotation(resultRotation);  //GetPawn()->SetActorRotation(resultRotation);
       // ((APlayerController*) ((AMAIController*) AIOwner)->GetGameRep()->Original)->AddPitchInput(resultRotation.Pitch);
        UE_LOG(LogTemp, Warning, TEXT("Actor rotation is %s"), *AIOwner->GetPawn()->GetActorRotation().ToString());
        ((AMAIController*) AIOwner)->GetGameRep()->Original->SetViewTarget(AIOwner->GetPawn());
        if(ticktime >= 60 && (InitialRot - resultRotation).Yaw < 0.01 && (InitialRot - resultRotation).Pitch < 0.01)
        {
            FireGun();
            ticktime = 0;
        }
    }
    ticktime++;
}

void UMAIBrainComponent::FireGun()
{
    if(((AMAIController*) AIOwner)->GetGameRep()->GetFireBindDelegate()->GetActionName() == "Fire")
        ((AMAIController*) AIOwner)->GetGameRep()->GetFireBindDelegate()->ActionDelegate.Execute("");
}

FVector UMAIBrainComponent::GetAbsMuzzleVec(FRotator InitialRot)
{
    return ((((AMAIController*) AIOwner)->GetGameRep()->GetMuzzle() != nullptr) ?
                                    ((AMAIController*) AIOwner)->GetGameRep()->GetMuzzle()->GetComponentLocation() : ((AMAIController*) AIOwner)->GetGameRep()->GetSelfLocation())
                    - InitialRot.RotateVector(FVector(100.0f, 0.0f, 10.0f));
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
