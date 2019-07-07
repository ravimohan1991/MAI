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
    UE_LOG(LogTemp, Warning, TEXT("Brain Ticking! AI owner is %s"), *AIOwner->GetName());
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    /*if(bShouldExplore)
    {
        ((AMAIController*) AIOwner)
    }*/
    //AIOwner->SetControlRotation(FRotator(0, deg * DeltaTime ,0));
    //AIOwner->GetPawn()->FaceRotation(FRotator(0, deg++ * DeltaTime ,0));
    AIOwner->GetPawn()->SetActorRotation(FRotator(0, deg++ * DeltaTime ,0));
}

