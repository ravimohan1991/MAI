// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShooterAIGameMode.h"
#include "ShooterAIHUD.h"
#include "ShooterAICharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Engine/StaticMesh.h"

AShooterAIGameMode::AShooterAIGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
    //static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/DummyCharacter"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShooterAIHUD::StaticClass();

    // for Tick purpose
    PrimaryActorTick.bCanEverTick = true;

}

void AShooterAIGameMode::BeginPlay()
{
    // spawn MAI's gamestate Actor
    MAIGameState = (AMAIGameState*) GetWorld()->SpawnActor(AMAIGameState::StaticClass());
    MAIGameState->SetGameMode(this);

    // spawn MAI's controller Actor
    MAIController = (AMAIController*) GetWorld()->SpawnActor(AMAIController::StaticClass());
    MAIController->SetGameRep(MAIGameState);

    // make MAI possess Dummy
    //MAIController->StartPossessing(FindPawns());

    //MAIGameState->SetTFocus(FindTFocus());

    // Save box actor references existing in the level
    BuildBoxArray();

    Super::BeginPlay();
}

void AShooterAIGameMode::PossessSelfPawn()
{
   //SelfPlayer->PossessedBy(MAIController);
   //MAIController->SetPawn(SelfPlayer);
   //MAIController->StartPossessing(SelfPlayer);
   //SelfPlayer->bUseControllerRotationYaw = true;
   /*AController* temp =  SelfPlayer->GetController();
   temp->UnPossess();
   temp->Possess(FindPawns());
   MAIController->StartPossessing(GetSelfPlayer());*/
   // MAIGameState->SetCameraManager(((APlayerController*) SelfPlayer->GetController() )->PlayerCameraManager);
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

APawn* AShooterAIGameMode::FindPawns()
{
    FString MeshRecognition(TEXT("Dummy"));
    FString Left(TEXT("l"));
    FString Right(TEXT("r"));

    for( TActorIterator<APawn> ActorItr(GetWorld()); ActorItr; ++ActorItr )
    {
        FString tempst(*ActorItr->GetName());
        if(tempst.Split(*MeshRecognition, &Left, &Right))
        {
           UE_LOG(LogTemp, Warning, TEXT("Goccha"), *ActorItr->GetName());
           return  *ActorItr;
        }

    }
    return nullptr;
}
/*
USceneComponent* AShooterAIGameMode::FindTFocus()
{
    FString UFocusRecognition(TEXT("targetfo"));
    FString Left(TEXT("l"));
    FString Right(TEXT("r"));

    for( TActorIterator<USceneComponent> ActorItr(GetWorld()); ActorItr; ++ActorItr )
    {
        FString tempst(*ActorItr->GetName());
        if(tempst.Split(*UFocusRecognition, &Left, &Right))
        {
           return  *ActorItr;
        }

    }
    return nullptr;
}
*/
void AShooterAIGameMode::Tick( float DeltaSeconds )
{
    //UE_LOG(LogTemp, Warning, TEXT("Tick() working"));
    // store player's current position
    MAIGameState->SetSelfLocation(SelfPlayer->GetActorLocation());
    //UE_LOG(LogTemp, Warning, TEXT("Tick() working. Self location is %s"), *MAIGameState->GetSelfLocation().ToString());
    //FindPawns();
    //ShowBox();
    Super::Tick(DeltaSeconds);
}

void AShooterAIGameMode::ShowBox()
{
    for( auto& Box : MAIGameState->GetWhiteBoxes() )
    {
        UE_LOG(LogTemp, Warning, TEXT("Number of Boxes is %d. Box location is %s"), BoxNum, *((AStaticMeshActor*) Box)->GetActorLocation().ToString());
    }
}
