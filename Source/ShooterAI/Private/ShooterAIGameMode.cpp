// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShooterAIGameMode.h"
#include "ShooterAIHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Engine/StaticMesh.h"
#include "ShooterAIDummy.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"


AShooterAIGameMode::AShooterAIGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
    // static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/DummyCharacter"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShooterAIHUD::StaticClass();

    // for Tick purpose
    PrimaryActorTick.bCanEverTick = false;

}

void AShooterAIGameMode::BeginPlay()
{
    // spawn MAI's gamestate Actor
    MAIGameState = (AMAIGameState*) GetWorld()->SpawnActor(AMAIGameState::StaticClass());
    MAIGameState->SetGameMode(this);

    // spawn MAI's controller Actor
    MAIController = (AMAIController*) GetWorld()->SpawnActor(AMAIController::StaticClass());
    MAIController->SetGameRep(MAIGameState);

    // Save box actor references existing in the level
    BuildBoxArray();

    Super::BeginPlay();
}

void AShooterAIGameMode::DoInitialization()
{
    // For input purposes
    EnableInput((APlayerController*)SelfPlayer->GetController());
    InputComponent->BindKey(FKey(FName("O")), EInputEvent::IE_Pressed, this, &AShooterAIGameMode::PressedO);
    InputComponent->BindKey(FKey(FName("I")), EInputEvent::IE_Pressed, this, &AShooterAIGameMode::PressedI);
    InputComponent->BindKey(FKey(FName("F")), EInputEvent::IE_Pressed, this, &AShooterAIGameMode::FireTest);

    MAIGameState->SetMuzzle(((AShooterAIDummy*) SelfPlayer)->FP_MuzzleLocation);
    MAIGameState->SetSelfPawn(SelfPlayer);
    MAIGameState->SetOriginalController((APlayerController*) SelfPlayer->GetController());
}

void AShooterAIGameMode::FireTest()
{
    MAIGameState->GetFireBindDelegate()->ActionDelegate.Execute(FKey(FName("LeftMouseButton")));
}

void AShooterAIGameMode::PressedO()
{
    FRotator temp = SelfPlayer->GetControlRotation();
    MAIController->Possess(SelfPlayer);
    SelfPlayer->Controller->SetControlRotation(temp);
}

void AShooterAIGameMode::PressedI()
{
    //UE_LOG(LogTemp, Warning, TEXT("Pressed 2"));
    FRotator temp = SelfPlayer->GetControlRotation();
    MAIGameState->GetOriginalController()->Possess(SelfPlayer);
    SelfPlayer->Controller->SetControlRotation(temp);
}


void AShooterAIGameMode::BuildBoxArray()
{
    // estimate the number of boxes in the level. Learned from Rama's tutorial
    // https://wiki.unrealengine.com/Iterators:_Object_%26_Actor_Iterators,_Optional_Class_Scope_For_Faster_Search
    FString MeshRecognition(TEXT("EditorCube"));
    FString Left(TEXT("l"));
    FString Right(TEXT("r"));
    for( TActorIterator<AStaticMeshActor> ActorItr(GetWorld()); ActorItr; ++ActorItr )
    {
        FString tempst(*ActorItr->GetName());
        if(tempst.Split(*MeshRecognition, &Left, &Right))
        {
           UE_LOG(LogTemp, Warning, TEXT("Static Mesh recognized is %s"), *ActorItr->GetName());
           MAIGameState->AddWhiteBox(*ActorItr);
           BoxNum++;
        }
    }
}

void AShooterAIGameMode::RedHit()
{
    HitScore += 100;
    MAIGameState->GetBlackBoard()->SetValueAsFloat(FName("PlayerScore"), HitScore);
}

void AShooterAIGameMode::BlueHit()
{
    HitScore -= 10;
    MAIGameState->GetBlackBoard()->SetValueAsFloat(FName("PlayerScore"), HitScore);
}

void AShooterAIGameMode::UpdateScore(float ScoreUpdate)
{
    HitScore += ScoreUpdate;
}

void AShooterAIGameMode::ShowBox()
{
    for( auto& Box : MAIGameState->GetWhiteBoxes() )
    {
        UE_LOG(LogTemp, Warning, TEXT("Number of Boxes is %d. Box location is %s"), BoxNum, *((AStaticMeshActor*) Box)->GetActorLocation().ToString());
    }
}
