// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MAI/Public/MAIGameState.h"
#include "MAI/Public/MAIController.h"

#include "ShooterAIGameMode.generated.h"

UCLASS(minimalapi, BlueprintType, Blueprintable)
class AShooterAIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterAIGameMode();

    /** For processing decisions and obtaining gamestate every frame. */
    void Tick( float DeltaSeconds ) override;

    /** For setting the Pawn player*/
    void SetSelfPlayer( APawn* Pawn ){SelfPlayer = Pawn;}// MAIGameState->SelfPawn = Pawn;}

    /** Accessing the self pawn. */
    APawn* GetSelfPlayer(){return SelfPlayer;}

    /** For possessing pawn by MAI. Called by ShooterAICharacter BeginPlay().*/
    void PossessSelfPawn();

    /** Estimate number of boxes in the level. */
    void BuildBoxArray();

    /** Experimental*/
    void ShowBox();

    /** Find pawns. */
    APawn* FindPawns();

    /***/
    void DoInitialization();

    void Pressed1();

    void Pressed2();

    void FirePawn();

    AMAIGameState* GetMAIGameState(){return  MAIGameState;}

private:
    /** MAIGamestate referance. */
    AMAIGameState* MAIGameState;

    /** Referance of Pawn. See BeginPlay() of ShooterAICharacter*/
    APawn* SelfPlayer;

    /** Number of white boxes. */
    int32 BoxNum;

    /** The MAI controller! */
    AMAIController* MAIController;

    /** Component that handles input for this actor, if input is enabled. */
    UPROPERTY()
    APawn* CInputComponent;

    AController* Original;

protected:
    /** Override BeginPlay() for spawning purposes. */
    void BeginPlay() override;
};



