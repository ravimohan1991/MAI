// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.

#pragma once

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "MAIGameState.h"
#include "MAIController.generated.h"

UCLASS()
class AMAIController : public AAIController
{
    GENERATED_BODY()

public:
    AMAIController();

    /** For processing decisions and obtaining gamestate every frame. */
    void Tick( float DeltaSeconds ) override;

    /** Setting the game state reference. */
    void SetGameRep( AMAIGameState* GR ){MAIGameRep = GR;}

    /** Find the closest box*/
    AStaticMeshActor* FindClosestBox();

protected:
    /** Override BeginPlay() for spawning BrainComponent. */
    void BeginPlay() override;

private:
    /** Representation of gamestate. */
    AMAIGameState* MAIGameRep;
};
