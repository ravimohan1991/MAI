// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#include "MAIBrainComponent.h"
#include "MAIController.h"

UMAIBrainComponent::UMAIBrainComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bTickInEditor = true;
    RewardEstimate.Add(0, 0);
    RewardEstimate.Add(1, 0);
    RewardEstimate.Add(2, 0);
    RewardEstimate.Add(3, 0);
    Number.Add(0, 0);
    Number.Add(1, 0);
    Number.Add(2, 0);
    Number.Add(3, 0);
}

void UMAIBrainComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
   // UE_LOG(LogTemp, Warning, TEXT("Brain Ticking! AI owner is %s"), *AIOwner->GetName());
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(/*bShouldExplore*/ AIOwner->GetPawn() && bGotReward)
    {
        //UE_LOG(LogTemp, Warning, TEXT("MAI Activated"));

        // see if any of the white box is at lineofsight. If yes, add it to seen white box
        CheckForLOSBoxes();
       // AStaticMeshActor* closest = FindClosestBox(((AMAIController*) AIOwner)->GetGameRep()->GetSeenWhiteBoxes());

        FRotator InitialRot = AIOwner->GetControlRotation();
        FVector InitialVec = InitialRot.Vector();

        if(bLookForBox)
        {
            AppBox = LookForAppBox(((AMAIController*) AIOwner)->GetGameRep()->GetSeenWhiteBoxes());
            bLookForBox = false;
        }
        FVector FinalVec = /*closest->GetActorLocation()*/ AppBox->GetActorLocation() - GetAbsMuzzleVec(InitialRot);

        FRotator FinalRotation = FinalVec.Rotation();
        const FRotator resultRotation = FMath::RInterpTo(InitialRot, FinalRotation, DeltaTime, 2.0);
        AIOwner->SetControlRotation(resultRotation);
        AIOwner->GetPawn()->SetActorRotation(AIOwner->GetControlRotation());

        ((AMAIController*) AIOwner)->GetGameRep()->GetOriginalController()->SetViewTarget(AIOwner->GetPawn());
        if(ticktime >= 60 && FMath::Abs<float>(InitialRot.Yaw - resultRotation.Yaw) < 0.01 && FMath::Abs<float>(InitialRot.Pitch - resultRotation.Pitch) < 0.01 && bShouldFire)
        {
            FireGun();
            ticktime = 0;
            bShouldFire = false;
            ScoreReward = ((AMAIController*) AIOwner)->GetGameRep()->GetBlackBoard()->GetValueAsFloat(FName("PlayerScore"));
            bGotReward = false;
        }
    }
    if (!bGotReward)
    {
        if(ScoreReward != ((AMAIController*) AIOwner)->GetGameRep()->GetBlackBoard()->GetValueAsFloat(FName("PlayerScore")))
        {
            bGotReward = true;
            bLookForBox = true;
            bShouldFire = true;
            UpdateEstimation();
        }
    }
    ticktime++;
}

void UMAIBrainComponent::UpdateEstimation()
{
    float reward = ((AMAIController*) AIOwner)->GetGameRep()->GetBlackBoard()->GetValueAsFloat(FName("PlayerScore")) - ScoreReward;
    Number[Action] += 1;
    RewardEstimate[Action] = RewardEstimate[Action] + 1 / Number[Action] * (reward - RewardEstimate[Action]);
}

AStaticMeshActor* UMAIBrainComponent::LookForAppBox( TArray<AStaticMeshActor*> ASMArray )
{
    float randNum = FMath::RandRange(0.0f, 1.0f);

    UE_LOG(LogTemp, Warning, TEXT("Random number is %f"), randNum);
    if(randNum >= epsilon)
    {
        UE_LOG(LogTemp, Warning, TEXT("Exploiting"));
        float Max = 0;
        TArray <int> MaxArray;
        // exploitation
        for(auto arr = RewardEstimate.CreateIterator(); arr; ++arr)
        {
            if(arr.Value() >= Max)
            {
                Max = arr.Value();
                MaxArray.Add(arr.Key());
            }
        }
        Action = FMath::RandRange(int(0), int(MaxArray.Num()) - 1);
        UE_LOG(LogTemp, Warning, TEXT("Action is %d"), Action);
        return ASMArray.GetData()[MaxArray.GetData()[Action]];
    }
    else
    {
        Action = FMath::RandRange(int32(0), int32(3));
        UE_LOG(LogTemp, Warning, TEXT("exploring with action %d"), Action);
        return ASMArray.GetData()[Action];
    }

    return nullptr;
}

void UMAIBrainComponent::FireGun()
{
    if(((AMAIController*) AIOwner)->GetGameRep()->GetFireBindDelegate()->GetActionName() == "Fire")
    {
        ((AMAIController*) AIOwner)->GetGameRep()->GetFireBindDelegate()->ActionDelegate.Execute("");
    }
}

FVector UMAIBrainComponent::GetAbsMuzzleVec(FRotator InitialRot)
{
    return ((((AMAIController*) AIOwner)->GetGameRep()->GetMuzzle() != nullptr) ?
                                    ((AMAIController*) AIOwner)->GetGameRep()->GetMuzzle()->GetComponentLocation() : AIOwner->GetPawn()->GetActorLocation())
                    - InitialRot.RotateVector(FVector(100.0f, 0.0f, 10.0f));
}

void UMAIBrainComponent::CheckForLOSBoxes()
{
    for(auto& Box : ((AMAIController*) AIOwner)->GetGameRep()->GetWhiteBoxes())
    {
        if(AIOwner->LineOfSightTo(Box, AIOwner->GetPawn()->GetPawnViewLocation()))//FVector(0, 0, 0)))
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
