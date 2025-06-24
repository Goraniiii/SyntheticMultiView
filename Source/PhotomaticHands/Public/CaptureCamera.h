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

    /** ��庰�� ĸó (RGB, SEG ��) */
    UFUNCTION(BlueprintCallable, Category = "Capture")
    void CaptureMode(const FString& ModeName, UMaterialInterface* OptionalMaterial);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "Capture")
    UTextureRenderTarget2D* RenderTarget;

    /** ���� �Կ��� ��� �̸� (���� �̸� prefix�� ����) */
    FString CurrentModeName;

    void ApplyPostProcess(UMaterialInterface* Material);
    void RemovePostProcess();

    void SaveImage();
	
};
