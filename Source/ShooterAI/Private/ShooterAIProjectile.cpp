// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShooterAIProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

AShooterAIProjectile::AShooterAIProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AShooterAIProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
    ProjectileMovement->ProjectileGravityScale = 0;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AShooterAIProjectile::BeginPlay()
{
    Super::BeginPlay();

    // Method to talk to gamemode. Store self referance in Gamemode and let MAI posses itself
    GameMode = GetWorld()->GetAuthGameMode<AShooterAIGameMode>();
}

void AShooterAIProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
        //OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

        AStaticMeshActor* temp = (AStaticMeshActor*) OtherActor;
        if(temp)
        {
            UMaterialInterface* tempMat = temp->GetStaticMeshComponent()->GetMaterial(0);
            //UE_LOG(LogTemp, Warning, TEXT("The color material is %s"), *tempMat->GetName());
            if(tempMat->GetName() == "CubeMaterial_Red")
                GameMode->RedHit();
            else
                GameMode->BlueHit();
        }
		Destroy();
	}
}
