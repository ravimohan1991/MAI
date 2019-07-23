#include "ShooterAIDummy.h"
#include "ShooterAIProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "ShooterAIGameMode.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

AShooterAIDummy::AShooterAIDummy()
{
    // set our turn rates for input
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    static ConstructorHelpers::FClassFinder<AShooterAIProjectile> ProjectileClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonProjectile"));
    ProjectileClass = ProjectileClassFinder.Class;

    static ConstructorHelpers::FObjectFinder<USoundBase> FireSoundObj(TEXT("/Game/FirstPerson/Audio/FirstPersonTemplateWeaponFire02.FirstPersonTemplateWeaponFire02"));
    if(FireSoundObj.Succeeded())
        FireSound = FireSoundObj.Object;

    // Create a CameraComponent
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());//SK_Mannequin, FName("head"));
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    SK_Mannequin = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DummyMesh"));
    SK_Mannequin->SetupAttachment(GetCapsuleComponent());

    // Create a gun mesh component
   // FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
    //FP_Gun->SetupAttachment(SK_Mannequin);//, FName("hand_r"));

    // Default offset from the character location for projectiles to spawn
    GunOffset = FVector(100.0f, 0.0f, 10.0f);

    FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
    FP_MuzzleLocation->SetupAttachment(SK_Mannequin);

   // bUseControllerRotationPitch = true;
}

void AShooterAIDummy::BeginPlay()
{
    Super::BeginPlay();

    // Method to talk to gamemode. Store self referance in Gamemode and let MAI posses itself
    GameMode = GetWorld()->GetAuthGameMode<AShooterAIGameMode>();
    if(GameMode)
    {
        GameMode->SetSelfPlayer(this);
        GameMode->DoInitialization();
        GameMode->GetMAIGameState()->SetFireBindDelegate(FireAction);
    }
}

//////////////////////////////////////////////////////////////////////////
// Input

void AShooterAIDummy::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // set up gameplay key bindings
    check(PlayerInputComponent);

    // Bind jump events
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    // Bind fire event
    FireAction  = &PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShooterAIDummy::OnFire);

    // Bind movement events
    PlayerInputComponent->BindAxis("MoveForward", this, &AShooterAIDummy::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AShooterAIDummy::MoveRight);

    // We have 2 versions of the rotation bindings to handle different kinds of devices differently
    // "turn" handles devices that provide an absolute delta, such as a mouse.
    // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &AShooterAIDummy::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterAIDummy::LookUpAtRate);
}

void AShooterAIDummy::OnFire()
{
    if(ProjectileClass != NULL)
    {
        UWorld* const World = GetWorld();
        if(World != NULL)
        {
            const FRotator SpawnRotation = GetControlRotation();

            // MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
            const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

            //Set Spawn Collision Handling Override
            FActorSpawnParameters ActorSpawnParams;
            ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

            // spawn the projectile at the muzzle
            World->SpawnActor<AShooterAIProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
        }
    }

    // try and play the sound if specified
    if (FireSound != NULL)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
    }

    // try and play a firing animation if specified
    if (FireAnimation != NULL)
    {
        // Get the animation object for the arms mesh
        UAnimInstance* AnimInstance = SK_Mannequin->GetAnimInstance();
        if (AnimInstance != NULL)
        {
            AnimInstance->Montage_Play(FireAnimation, 1.f);
        }
    }
}


void AShooterAIDummy::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        // add movement in that direction
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void AShooterAIDummy::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        // add movement in that direction
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void AShooterAIDummy::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AShooterAIDummy::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
