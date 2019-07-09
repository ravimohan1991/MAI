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

    /*if(bShouldExplore)
    {
        ((AMAIController*) AIOwner)
    }*/
    UE_LOG(LogTemp, Warning, TEXT("Attempt to rotate Dummy by %d degrees"), int32(deg * DeltaTime));

    FRotator temp = AIOwner->GetPawn()->GetActorRotation();

    const FRotator resultRotation = FMath::RInterpTo( temp, temp + FRotator(0, 10, 0), DeltaTime, 2.0 );
    //AIOwner->GetPawn()->SetActorRotation(resultRotation);
    ((AMAIController*) AIOwner)->FindDummy()->SetActorRotation(resultRotation);
    ((AMAIController*) AIOwner)->FindDummy()->GetController()->SetControlRotation(resultRotation);
}

