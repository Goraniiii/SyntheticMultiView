// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureCamera.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "TimerManager.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include <ImageUtils.h>

ACaptureCamera::ACaptureCamera()
{
    PrimaryActorTick.bCanEverTick = false;

    // render target
    //RenderTarget = NewObject<UTextureRenderTarget2D>();
    //RenderTarget->InitAutoFormat(512, 512);
    //RenderTarget->ClearColor = FLinearColor::Black;
    //RenderTarget->UpdateResourceImmediate(true);

    //RenderTarget = GetCaptureComponent2D()->TextureTarget;

    // capture component
    //GetCaptureComponent2D()->TextureTarget = RenderTarget;
    GetCaptureComponent2D()->bCaptureEveryFrame = false;
    GetCaptureComponent2D()->bCaptureOnMovement = false;

    GetCaptureComponent2D()->CaptureSource = ESceneCaptureSource::SCS_SceneColorHDR;

}

void ACaptureCamera::BeginPlay()
{
    Super::BeginPlay();
}

void ACaptureCamera::CaptureMode(const FString& ModeName, UMaterialInterface* OptionalMaterial)
{
    CurrentModeName = ModeName;

    GetCaptureComponent2D()->CaptureScene();

    // delay for save
    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ACaptureCamera::SaveImage, 0.7f, false);
}

void ACaptureCamera::SaveImage()
{
    RenderTarget = GetCaptureComponent2D()->TextureTarget;

    if (!RenderTarget)
    {
        UE_LOG(LogTemp, Error, TEXT("RenderTarget is invalid."));
        return;
    }

    FRenderTarget* RenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();

    TArray<FColor> Bitmap;
    RenderTargetResource->ReadPixels(Bitmap);

    TArray<uint8> PNGData;
    FImageUtils::CompressImageArray(RenderTarget->SizeX, RenderTarget->SizeY, Bitmap, PNGData);

    FString FilePath = FPaths::ProjectSavedDir() / TEXT("Captures");
    FString FileName = FString::Printf(TEXT("%s/%s_%s.png"), *FilePath,
        *FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S")), *CurrentModeName);

    FFileHelper::SaveArrayToFile(PNGData, *FileName);

    UE_LOG(LogTemp, Log, TEXT("Saved image to: %s"), *FileName);
}