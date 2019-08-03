// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.
#pragma once

#include "MAI/Public/MAIController/MAIController.h"
#include "MAIPlayerController.generated.h"

UCLASS()
class AMAIPlayerController : public AMAIController
{
    GENERATED_BODY()

public:
    AMAIPlayerController();

    void Tick( float DeltaSeconds ) override;

    UFUNCTION(BlueprintCallable, Category="MAI")
    void PrintLog();

    UFUNCTION(BlueprintCallable, Category="MAI")
    void UpdateEstimates();

    UFUNCTION(BlueprintCallable, Category="MAI")
    void LookForAppBox();

    UFUNCTION(BlueprintCallable, Category="MAI")
    bool RotateTowardBox();

    FVector GetAbsMuzzleVec(FRotator InitialRot);

    UFUNCTION(BlueprintCallable, Category="MAI")
    void EvaluateReward();

    UFUNCTION(BlueprintCallable, Category="MAI")
    void Fire();

public:

    UPROPERTY(BlueprintReadWrite, Category="MAI")
    int Action = -1;

    UPROPERTY(BlueprintReadWrite, Category="MAI")
    bool bShouldLookForBox = true;

    UPROPERTY(BlueprintReadWrite, Category="MAI")
    int ticktime = 0;

    UPROPERTY(BlueprintReadWrite, Category="MAI")
    bool bShouldFire = true;

    UPROPERTY(BlueprintReadWrite, Category="MAI")
    float Reward = 0;

    void PrintMaxEsArray( TArray<int> MaxArr);

protected:
    /** Override for brain component initialization. */
    void BeginPlay() override;

private:
    /** For estimation purpose. */
    TMap <int, float> RewardEstimate;

    /** Action number counter. */
    TMap <int, int> Number;

    float epsilon = 0.1;
};
