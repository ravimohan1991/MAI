// (ɔ) The_Cowboy 1000 BC - 2019 AD. All rights reversed.


#pragma once

#include "GameFramework/Info.h"
#include "Vector.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/GameModeBase.h"
#include "MAI/Public/Blackboard/MAIBlackboardComponent.h"
#include "MAIGameState.generated.h"

UCLASS()
class AMAIGameState : public AInfo
{
    GENERATED_BODY()

private:
    /** Controller class the game began with (actually APlayerController)*/
    APlayerController* Original;

    /** Reference to the APawn playing. */
    APawn* SelfPawn;

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

    /** Blackboard reference. */
    UPROPERTY(BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
    UMAIBlackboardComponent* BlackBoard;


private:
    /** Reference for place of shooting projectile. */
    class USceneComponent* FP_MuzzleLocation;

    /** Reference to firing delegate. */
    FInputActionBinding FireBindDelegate;

public:

    /** Getting the APawn pointer of shooter.*/
    APawn* GetSelfPawn(){return SelfPawn;}

    /** Setting the shooter APawn.*/
    UFUNCTION()
    void SetSelfPawn( APawn* Pawn ){SelfPawn = Pawn;}

    /** Returning FVector array pointer. */
    UFUNCTION()
    TArray<AStaticMeshActor*> GetWhiteBoxes(){return WhiteBoxes;}

    /** Add elements in box array. */
    void AddWhiteBox( AStaticMeshActor* SActor ){WhiteBoxes.Add(SActor);}

    /** Not functional. */
    void AddSeenWhiteBoxes( AStaticMeshActor* SActor ){SeenWhiteBoxes.Add(SActor);}

    /** Not functional. */
    void RemoveSeenWhiteBoxes( AStaticMeshActor* SActor ){SeenWhiteBoxes.Remove(SActor);}

    UFUNCTION(BlueprintCallable, Category = "MAI")
    TArray<AStaticMeshActor*> GetSeenWhiteBoxes();//{return SeenWhiteBoxes;}

    /** Set GameMode. */
    void SetGameMode( AGameModeBase* GMode ){GameMode = GMode;}

    /** Get GameMode. */
    AGameModeBase* GetGameMode(){return GameMode;}

    /** Memorizing the gun muzzle component. */
    void SetMuzzle(USceneComponent* USC){FP_MuzzleLocation = USC;}

    /** Getting the gun muzzle component. */
    USceneComponent* GetMuzzle(){return FP_MuzzleLocation;}

public:
    /** Storing the fire delegate binding. */
    void SetFireBindDelegate(FInputActionBinding* Del){FireBindDelegate = *Del;}

    /** Getting the fire delegate binging. */
    FInputActionBinding* GetFireBindDelegate(){return &FireBindDelegate;}

    void SetOriginalController( APlayerController* Cont ){Original = Cont;}

    APlayerController* GetOriginalController(){return Original;}

    void SetBlackBoard( UMAIBlackboardComponent* SomeBB ){BlackBoard = SomeBB;}

    UFUNCTION(BlueprintCallable, Category = "MAI")
    UMAIBlackboardComponent* GetBlackBoard(){return BlackBoard;}
};
