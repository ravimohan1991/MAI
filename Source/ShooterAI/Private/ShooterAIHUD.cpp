// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShooterAIHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "ShooterAIDummy.h"

AShooterAIHUD::AShooterAIHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;

}


void AShooterAIHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );

    float XL, YL;

    // position for drawing score
    Canvas->StrLen(GEngine->GetMediumFont(), FString("Score:"), XL, YL);
    Canvas->SetDrawColor(255, 0 , 0);
    if((AShooterAIDummy*)this->GetOwningPawn())
        Canvas->DrawText(GEngine->GetLargeFont(), FString("Score: " + FString::SanitizeFloat( ((AShooterAIDummy*)this->GetOwningPawn())->PlayerScore )), Canvas->ClipX - 3 * XL, Canvas->ClipY * 0.2);
}

void AShooterAIHUD::BeginPlay()
{
    Super::BeginPlay();
    GameMode = GetWorld()->GetAuthGameMode<AShooterAIGameMode>();
}
