// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.


#pragma once

#include "GameFramework/Info.h"
#include "Vector.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/GameModeBase.h"
#include "MAIGameState.generated.h"

UCLASS()
class AMAIGameState : public AInfo
{
    GENERATED_BODY()

private:
    /** The location of the Shooter.*/
    UPROPERTY()
    FVector SelfLocation;

    /** The location of white boxes stored dynamically! I am assuming
        number of boxes don't change in the level. */
    UPROPERTY()
    TArray<AStaticMeshActor*> WhiteBoxes;

    /** The gamemode referance. */
    AGameModeBase* GameMode;

public:
    /** Getting current location of the Shooter.*/
    UFUNCTION()
    FVector GetSelfLocation(){return SelfLocation;}

    /** Setting current location of the Shooter.*/
    UFUNCTION()
    void SetSelfLocation( FVector Location ){SelfLocation = Location;}

    /** Returning FVector array pointer. */
    UFUNCTION()
    TArray<AStaticMeshActor*> GetWhiteBoxes(){return WhiteBoxes;}

    /** Add elements in box array. */
    void AddWhiteBox( AStaticMeshActor* SActor ){WhiteBoxes.Add(SActor);}

    /** Set GameMode. */
    void SetGameMode( AGameModeBase* GMode ){GameMode = GMode;}

    /** Get GameMode. */
    AGameModeBase* GetGameMode(){return GameMode;}

};
