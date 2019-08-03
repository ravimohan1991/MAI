// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MAI/Public/MAIGameState.h"
#include "MAI/Public/MAIController/MAIPlayerController.h"

#include "ShooterAIGameMode.generated.h"

UCLASS(minimalapi, BlueprintType, Blueprintable)
class AShooterAIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterAIGameMode();

    /** For setting the Pawn player*/
    void SetSelfPlayer( APawn* Pawn ){SelfPlayer = Pawn;}

    /** Accessing the self pawn. */
    APawn* GetSelfPlayer(){return SelfPlayer;}

    /** Estimate number of boxes in the level. */
    void BuildBoxArray();

    /** Experimental*/
    void ShowBox();

    /** Setting elements from ShooterAIDummy class. */
    void DoInitialization();

    /** Method called on key press. */
    void PressedO();

    /** Method called on key press. */
    void PressedI();

    /** Fore returning gamestate. */
    AMAIGameState* GetMAIGameState(){return  MAIGameState;}

    void FireTest();

    /** Updating the score. */
   // void UpdateScore( float ScoreUpdate );

    /** Function called on Red hit. */
    void RedHit(APawn* Pawn);

    /** Function called on Blue hit. */
    void BlueHit(APawn* Pawn);

    /** Incrementing score. */
    void IncrementPawnAIScore(APawn* Pawn, float Score);

    void SetGameReps();

private:
    /** MAIGamestate referance. */
    AMAIGameState* MAIGameState;

    /** Referance of Pawn. See BeginPlay() of ShooterAICharacter*/
    APawn* SelfPlayer;

    /** Number of white boxes. */
    int32 BoxNum;

    /** The MAI player controller! */
    TSubclassOf<AMAIPlayerController> MAIContObj;
    AMAIPlayerController* MAIController;

    /** The score. */
    //float HitScore;

   // TMap <APawn*, float> HitScore;

protected:
    /** Override BeginPlay() for spawning purposes. */
    void BeginPlay() override;
};



