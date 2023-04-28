// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "openvr.h"
#include "VRFrontCamera.generated.h"


class UTexture2D;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIROMOVE_API UVRFrontCamera : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVRFrontCamera();
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetCameraFrame();

protected:
	virtual void BeginPlay() override;

private:
	void StarVideoPreview();
	//returns false if frame didn't change since last time, so we can keep previous frame
	bool AcquireCameraFrame();
	bool InitializeWebcameraComponent();

	vr::IVRTrackedCamera* hmdCamera;
	vr::TrackedCameraHandle_t	m_hTrackedCamera;
	uint32 m_nCameraFrameWidth;
	uint32 m_nCameraFrameHeight;
	uint32 m_nCameraFrameBufferSize;
	uint32 m_nLastFrameSequence;
	uint8_t *m_pCameraFrameBuffer;

	UPROPERTY()
	UTexture2D* m_cameraFrame;
};
