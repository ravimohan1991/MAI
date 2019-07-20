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

    /** Look for appropriate box. */
    AStaticMeshActor* LookForAppBox( TArray<AStaticMeshActor*> ASMArray );

private:
    /** Exploration flag. */
    bool bShouldExplore = true;

    /** Closest box pointer. */
    AStaticMeshActor* AppBox = nullptr;

    float deg = 0;

    /** Tick counter. */
    int ticktime = 0;

    /** Should fire. Gives enough ticks to
     *  compute between two fire.
     */
    bool bShouldFire = true;

private:
    //TArray <float> RewardEstimate;

    TMap <int, float> RewardEstimate;

    TMap <int, int> Number;

    float epsilon = 0.1;

    bool bGotReward= true;

    bool bLookForBox = true;

    float ScoreReward = 0;

    int Action = -1;

public:
    void UpdateEstimation();
};
