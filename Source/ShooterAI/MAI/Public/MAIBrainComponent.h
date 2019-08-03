// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#pragma once

#include "Runtime/AIModule/Classes/BrainComponent.h"
#include "MAI/Public/MAIController/MAIController.h"
#include "MAIBrainComponent.generated.h"

UCLASS(ClassGroup = MAI, BlueprintType, Blueprintable)
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
    UFUNCTION(BlueprintCallable, Category = "MAI")
    FVector GetAbsMuzzleVec(FRotator InitialRot);

    /** Function for invoking OnFire() method (in ShooterAIDummy). */
    UFUNCTION(BlueprintCallable, Category = "MAI")
    void FireGun();

    /** Look for appropriate box. */
    UFUNCTION(BlueprintCallable, Category = "MAI")
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

    int Iteration = 0;

public:
    UFUNCTION(BlueprintCallable, Category = "MAI")
    void UpdateEstimation();

    void PrintEstimates();

    void PrintMaxEsArray( TArray<int> MaxArr);

    UFUNCTION(BlueprintCallable, Category = "MAI")
    bool GetGotReward();//{return bGotReward;}

    UFUNCTION(BlueprintCallable, Category = "MAI")
    void SetGotReward( bool bGReward );

    UFUNCTION(BlueprintCallable, Category = "MAI")
    bool GetLookForBox();

    UFUNCTION(BlueprintCallable, Category = "MAI")
    void SetLookForBox( bool bLForBox );

    UFUNCTION(BlueprintCallable, Category = "MAI")
    bool GetShouldFire();

    UFUNCTION(BlueprintCallable, Category = "MAI")
    void SetShouldFire( bool SFire );

    UFUNCTION(BlueprintCallable, Category = "MAI")
    float GetScoreReward();

    UFUNCTION(BlueprintCallable, Category = "MAI")
    void SetScoreReward( float Score );

    UFUNCTION(BlueprintCallable, Category = "MAI")
    void IncrementTick(){ticktime++;}

    UFUNCTION(BlueprintCallable, Category = "MAI")
    void ResetTickCounter(){ticktime = 0;}

    UFUNCTION(BlueprintCallable, Category = "MAI")
    float GetTick(){return ticktime;}
};
