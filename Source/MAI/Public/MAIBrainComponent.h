// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#pragma once

#include "Runtime/AIModule/Classes/BrainComponent.h"
#include "MAIController.h"
#include "MAIBrainComponent.generated.h"

UCLASS()
class UMAIBrainComponent : public UBrainComponent
{
    GENERATED_BODY()

public:
    UMAIBrainComponent();

    /** Ticking for heuristics. */
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    /***/
    void CheckForLOSBoxes();

    /** Find the closest box*/
    AStaticMeshActor* FindClosestBox( TArray<AStaticMeshActor*> ASMArray );

    /** Absolute muzzle */
    FVector GetAbsMuzzleVec(FRotator InitialRot);

    /** Function for invoking OnFire() method (in ShooterAIDummy). */
    void FireGun();

private:
    /** Exploration flag. */
    bool bShouldExplore = true;

    /** Closest box pointer. */
    AStaticMeshActor* Closest = nullptr;

    float deg = 0;

    /** Tick counter. */
    int ticktime = 0;
};
