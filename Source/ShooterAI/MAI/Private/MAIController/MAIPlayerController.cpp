// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#include "MAI/Public/MAIController/MAIPlayerController.h"
#include "MAI/Public/MAIBrainComponent.h"
#include "ShooterAIDummy.h"
#include "ShooterAIDummyAI.h"

AMAIPlayerController::AMAIPlayerController()
{
     PrimaryActorTick.bCanEverTick = true;
     RewardEstimate.Add(0, 0);
     RewardEstimate.Add(1, 0);
     RewardEstimate.Add(2, 0);
     RewardEstimate.Add(3, 0);
     Number.Add(0, 0);
     Number.Add(1, 0);
     Number.Add(2, 0);
     Number.Add(3, 0);
}

void AMAIPlayerController::BeginPlay()
{
   // BrainComponent = NewObject<UMAIBrainComponent>(this);
   // BrainComponent->RegisterComponent();

    Super::BeginPlay();
}

void AMAIPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    //if((AShooterAIDummy*)GetPawn())
      //  UE_LOG(LogTemp, Warning, TEXT("Player score is %f"), ((AShooterAIDummy*)GetPawn())->PlayerScore);
}

void AMAIPlayerController::PrintLog()
{
    UE_LOG(LogTemp, Warning, TEXT("Running from C++ code."));
}

void AMAIPlayerController::UpdateEstimates()
{
    float reward = ((AShooterAIDummy*)GetPawn())->PlayerScore - CachedScore;
    Number[Action] += 1;
    RewardEstimate[Action] = RewardEstimate[Action] + 1 / Number[Action] * (reward - RewardEstimate[Action]);
}

void AMAIPlayerController::LookForAppBox()
{
    float randNum = FMath::RandRange(0.0f, 1.0f);

    if(randNum >= epsilon)// Exploit
    {
        float Max = -1;
        TArray <int> MaxArray;
        for (auto arr = RewardEstimate.CreateIterator(); arr; ++arr)
        {
                if(arr.Value() >= Max)
                    Max = arr.Value();
        }
        for(auto arr = RewardEstimate.CreateIterator(); arr; ++arr)
        {
            if(arr.Value() == Max)
            {
                MaxArray.Add(arr.Key());
            }
        }
        PrintMaxEsArray(MaxArray);
        Action = MaxArray.GetData()[FMath::RandRange(int(0), int(MaxArray.Num()) - 1)];// random from max estimates
        UE_LOG(LogTemp, Warning, TEXT("|Action is %d"), Action);
    }
    else
    {
         Action = FMath::RandRange(int32(0), int32(3));
    }
}

void AMAIPlayerController::PrintMaxEsArray(TArray<int> MaxArr)
{
    UE_LOG(LogTemp, Warning, TEXT("|Maximum estimates is/are:"));
    for (auto& it : MaxArr)
    {
        UE_LOG(LogTemp, Warning, TEXT("|     Q(%d) = %f"), it, RewardEstimate[it]);
    }
}

bool AMAIPlayerController::RotateTowardBox()
{
    AStaticMeshActor* target = GetGameRep()->GetWhiteBoxes()[Action];

    UE_LOG(LogTemp, Warning, TEXT("The action is %d"), Action);
    FRotator InitialRot = GetControlRotation();

    FVector FinalVec = target->GetActorLocation() - GetPawn()->GetActorLocation();//GetAbsMuzzleVec(InitialRot);
    FRotator FinalRotation = FinalVec.Rotation();
    SetControlRotation(FinalRotation);//resultRotation);
    GetPawn()->SetActorRotation(FRotator(0, FinalRotation.Yaw, 0));

    CachedScore = ((AShooterAIDummy*)GetPawn())->PlayerScore;
    return true;
}


void AMAIPlayerController::Fire()
{
    ((AShooterAIDummyAI*)GetPawn())->OnFire();
}

FVector AMAIPlayerController::GetAbsMuzzleVec(FRotator InitialRot)
{
    return ((GetGameRep()->GetMuzzle() != nullptr) ?
                                    GetGameRep()->GetMuzzle()->GetComponentLocation() : GetPawn()->GetActorLocation())
                    + InitialRot.RotateVector(FVector(100.0f, 0.0f, 10.0f));
}
