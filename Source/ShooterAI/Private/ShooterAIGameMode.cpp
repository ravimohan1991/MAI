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

    // Save box actor references existing in the level
    BuildBoxArray();

    Super::BeginPlay();
}

void AShooterAIGameMode::DoInitialization()
{
    Original = SelfPlayer->GetController();

    // For input purposes
    EnableInput((APlayerController*)Original);
    InputComponent->BindKey(FKey(FName("One")), EInputEvent::IE_Pressed, this, &AShooterAIGameMode::Pressed1);
    InputComponent->BindKey(FKey(FName("Two")), EInputEvent::IE_Pressed, this, &AShooterAIGameMode::Pressed2);

    MAIGameState->SetMuzzle(((AShooterAIDummy*)GetSelfPlayer())->FP_MuzzleLocation);
    MAIGameState->SelfPawn = SelfPlayer;
    MAIGameState->Original = (APlayerController*) Original;
}

void AShooterAIGameMode::Pressed1()
{
    //UE_LOG(LogTemp, Warning, TEXT("Pressed 1"));
    //MAIGameState->SetCameraManager(((APlayerController*) Original)->PlayerCameraManager);
    // memorizing is important because control rotations are rewritten on possession (as per actor
    // rotations which only consist of yaw)
    FRotator temp = SelfPlayer->GetControlRotation();
    MAIController->Possess(SelfPlayer);
    SelfPlayer->Controller->SetControlRotation(temp);
}

void AShooterAIGameMode::Pressed2()
{
    //UE_LOG(LogTemp, Warning, TEXT("Pressed 2"));
    FRotator temp = SelfPlayer->GetControlRotation();
    Original->Possess(SelfPlayer);
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
