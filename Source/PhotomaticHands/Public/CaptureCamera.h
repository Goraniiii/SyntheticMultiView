// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "CaptureCamera.generated.h"

/**
 * 
 */
UCLASS()
class PHOTOMATICHANDS_API ACaptureCamera : public ASceneCapture2D
{
	GENERATED_BODY()

public:
    ACaptureCamera();

    /** 모드별로 캡처 (RGB, SEG 등) */
    UFUNCTION(BlueprintCallable, Category = "Capture")
    void CaptureMode(const FString& ModeName, UMaterialInterface* OptionalMaterial);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "Capture")
    UTextureRenderTarget2D* RenderTarget;

    /** 현재 촬영할 모드 이름 (파일 이름 prefix로 사용됨) */
    FString CurrentModeName;

    void ApplyPostProcess(UMaterialInterface* Material);
    void RemovePostProcess();

    void SaveImage();
	
};
