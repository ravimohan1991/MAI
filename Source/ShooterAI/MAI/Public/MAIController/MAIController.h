// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#pragma once

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "MAI/Public/MAIGameState.h"
#include "MAIController.generated.h"

UCLASS(ClassGroup = MAI, BlueprintType, Blueprintable)
class AMAIController : public AAIController
{
    GENERATED_BODY()

public:
    AMAIController();

    /** For processing decisions and obtaining gamestate every frame. */
    void Tick( float DeltaSeconds ) override;

    /** Setting the game state reference. */
    void SetGameRep( AMAIGameState* GR );

    /** Getting the game state reference. */
    UFUNCTION(BlueprintCallable, Category = "MAI")
    AMAIGameState* GetGameRep(){return MAIGameRep;}

    /** For possessing a pawn. */
    UFUNCTION(BlueprintCallable, Category = "MAI")
    void StartPossessing( APawn* PPawn );

    /** Makeing GetPawn() Blueprint visible. */
    UFUNCTION(BlueprintCallable, Category = "MAI")
    APawn* MAIGetPawn(){return GetPawn();}

    /** Custom routine with cone implementation. */
    virtual bool LineOfSightTo(const AActor* Other, FVector ViewPoint = FVector(ForceInit), bool bAlternateChecks = false) const override;

    /** Cached score of the player. For reward estimation. */
    float CachedScore;

protected:
    /** Override BeginPlay() for spawning BrainComponent. */
    void BeginPlay() override;

private:
    /** Representation of gamestate. */
    AMAIGameState* MAIGameRep;
};
