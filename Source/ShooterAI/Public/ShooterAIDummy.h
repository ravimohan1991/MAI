#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterAIGameMode.h"

#include "ShooterAIDummy.generated.h"

UCLASS(config=Game)
class AShooterAIDummy : public ACharacter
{
    GENERATED_BODY()

public:
    AShooterAIDummy();

    /** Pawn mesh: 1st person view (arms; seen only by self) */
    UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
    class USkeletalMeshComponent* SK_Mannequin;

    /** Gun mesh: 1st person view (seen only by self) */
   // UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    //class USkeletalMeshComponent* FP_Gun;

    /** Location on gun mesh where projectiles should spawn. */
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    class USceneComponent* FP_MuzzleLocation;

    /** First person camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FirstPersonCameraComponent;

    /** The gamemode referance. */
    AShooterAIGameMode* GameMode;

    /** Fire bind delegate. */
    FInputActionBinding* FireAction;

protected:
    /** Fires a projectile. */
    void OnFire();

    /** Handles moving forward/backward */
    void MoveForward(float Val);

    /** Handles stafing movement, left and right */
    void MoveRight(float Val);

    /**
     * Called via input to turn at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void TurnAtRate(float Rate);

    /**
     * Called via input to turn look up/down at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void LookUpAtRate(float Rate);

public:
    /** Returns SK_Mannequin subobject **/
    FORCEINLINE class USkeletalMeshComponent* GetMeshSK_Mannequin() const { return SK_Mannequin; }
    /** Returns FirstPersonCameraComponent subobject **/
    FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:
    virtual void BeginPlay();

    // APawn interface
    virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
    // End of APawn interface

public:
    /** Projectile class to spawn */
    UPROPERTY(EditDefaultsOnly, Category=Projectile)
    TSubclassOf<class AShooterAIProjectile> ProjectileClass;

    /** Gun muzzle's offset from the characters location */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
    FVector GunOffset;

    /** Sound to play each time we fire */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
    class USoundBase* FireSound;

    /** AnimMontage to play each time we fire */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    class UAnimMontage* FireAnimation;

    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
    float BaseTurnRate;

    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
    float BaseLookUpRate;

};
