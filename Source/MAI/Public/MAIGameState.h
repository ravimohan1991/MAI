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

    /**
     * The location of white boxes stored dynamically!
     * I am assuming number of boxes don't change in
     * the level.
     */
    TArray<AStaticMeshActor*> WhiteBoxes;

    /**
     * For tracking boxes seen. Not
     * Not functional yet.
     */
    TArray<AStaticMeshActor*> SeenWhiteBoxes;

    /** The gamemode referance. */
    AGameModeBase* GameMode;

    /** Camera manager. */
    APlayerCameraManager* MPlayerCameraManager;

    /** Reference for place of shooting projectile. */
    class USceneComponent* FP_MuzzleLocation;

    /** Reference to firing delegate. */
    FInputActionBinding* FireBindDelegate;

public:

    /** Getting current location of the Shooter.*/
    FVector GetSelfLocation(){return SelfLocation;}

    /** Setting current location of the Shooter.*/
    UFUNCTION()
    void SetSelfLocation( FVector Location ){SelfLocation = Location;}

    /** Returning FVector array pointer. */
    UFUNCTION()
    TArray<AStaticMeshActor*> GetWhiteBoxes(){return WhiteBoxes;}

    /** Add elements in box array. */
    void AddWhiteBox( AStaticMeshActor* SActor ){WhiteBoxes.Add(SActor);}

    void AddSeenWhiteBoxes( AStaticMeshActor* SActor ){SeenWhiteBoxes.Add(SActor);}

    void RemoveSeenWhiteBoxes( AStaticMeshActor* SActor ){SeenWhiteBoxes.Remove(SActor);}

    TArray<AStaticMeshActor*> GetSeenWhiteBoxes(){return SeenWhiteBoxes;}

    /** Set GameMode. */
    void SetGameMode( AGameModeBase* GMode ){GameMode = GMode;}

    /** Get GameMode. */
    AGameModeBase* GetGameMode(){return GameMode;}

    /***/
    void SetCameraManager( APlayerCameraManager* PCM ){MPlayerCameraManager = PCM;}

    APlayerCameraManager* GetCameraManager(){return MPlayerCameraManager;}

    /***/
    void SetMuzzle(USceneComponent* USC){FP_MuzzleLocation = USC;}

    USceneComponent* GetMuzzle(){return FP_MuzzleLocation;}

    void SetFireBindDelegate(FInputActionBinding* Del){FireBindDelegate = Del;}

    FInputActionBinding* GetFireBindDelegate(){return FireBindDelegate;}

public:
     APawn* SelfPawn;
     APlayerController* Original;
};
