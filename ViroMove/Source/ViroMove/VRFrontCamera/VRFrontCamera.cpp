// Fill out your copyright notice in the Description page of Project Settings.

#include "VRFrontCamera.h"
#include "HeadMountedDisplay.h"
#include "Engine.h"
#include "EngineMinimal.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/Texture2D.h"

// Sets default values for this component's properties
UVRFrontCamera::UVRFrontCamera() :
	hmdCamera(nullptr), m_hTrackedCamera(INVALID_TRACKED_CAMERA_HANDLE), m_nCameraFrameWidth(0),
	 m_nCameraFrameHeight(0), 
	m_nCameraFrameBufferSize(0), m_nLastFrameSequence(0), m_pCameraFrameBuffer(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


UTexture2D * UVRFrontCamera::GetCameraFrame()
{
	if (!hmdCamera) return nullptr;
	if (!AcquireCameraFrame()) return m_cameraFrame;
	uint8* MipData = (uint8*)m_cameraFrame->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(MipData, (void*)m_pCameraFrameBuffer, m_nCameraFrameHeight * m_nCameraFrameWidth * 4);
	m_cameraFrame->PlatformData->Mips[0].BulkData.Unlock();
	m_cameraFrame->PlatformData->NumSlices = 1;
	m_cameraFrame->UpdateResource();
	return m_cameraFrame;
}

// Called when the game starts
void UVRFrontCamera::BeginPlay()
{
	Super::BeginPlay();
	if (!InitializeWebcameraComponent())
	{
		UE_LOG(LogTemp, Error, TEXT("UWebcameraComponent::BeginPlay() Initialization failed"));
		return;
	}
	StarVideoPreview();	
}

void UVRFrontCamera::StarVideoPreview()
{
	//// Allocate for camera frame buffer requirements
	uint32_t nCameraFrameBufferSize = 0;
	//VRTrackedCameraFrameType_Distorted
	if (hmdCamera->GetCameraFrameSize(vr::k_unTrackedDeviceIndex_Hmd,
		vr::VRTrackedCameraFrameType_Distorted, &m_nCameraFrameWidth, &m_nCameraFrameHeight,
		&nCameraFrameBufferSize) != vr::VRTrackedCameraError_None)
	{
		UE_LOG(LogTemp, Error, TEXT("UWebcameraComponent::StarVideoPreview GetCameraFrameSize failed\n"));
	}
	//auto settings = vr::VRSettings();
	////settings->SetBool(vr::k_pch_Camera_Section, vr::k_pch_Camera_EnableCameraForCollisionBounds_Bool, true);
	//settings->Sync(true);

	//auto chaperone = vr::VRChaperone();
	//vr::HmdColor_t color;
	//color.r = 0;
	//color.a = 0;
	//color.b = 0;
	//color.g = 0;
	//chaperone->SetSceneColor(color);
	if (nCameraFrameBufferSize && nCameraFrameBufferSize != m_nCameraFrameBufferSize)
	{
		m_cameraFrame = UTexture2D::CreateTransient(m_nCameraFrameWidth, m_nCameraFrameHeight, PF_R8G8B8A8);
		FMemory::Free(m_pCameraFrameBuffer);
		delete[] m_pCameraFrameBuffer;
		m_nCameraFrameBufferSize = nCameraFrameBufferSize;
		m_pCameraFrameBuffer = new uint8_t[m_nCameraFrameBufferSize];
		FMemory::Memset(m_pCameraFrameBuffer, 0, m_nCameraFrameBufferSize);
	}

	m_nLastFrameSequence = 0;
	hmdCamera->AcquireVideoStreamingService(vr::k_unTrackedDeviceIndex_Hmd, &m_hTrackedCamera);
	if (m_hTrackedCamera == INVALID_TRACKED_CAMERA_HANDLE)
	{
		UE_LOG(LogTemp, Error, TEXT("UWebcameraComponent::StarVideoPreview AcquireVideoStreamingService failed"));
	}
}

bool UVRFrontCamera::AcquireCameraFrame()
{
	vr::CameraVideoStreamFrameHeader_t frameHeader;
	vr::EVRTrackedCameraError nCameraError = hmdCamera->GetVideoStreamFrameBuffer(m_hTrackedCamera,
		vr::VRTrackedCameraFrameType_Undistorted, nullptr, 0, &frameHeader, sizeof(frameHeader));
	if (frameHeader.nFrameSequence == m_nLastFrameSequence) return false;
	nCameraError = hmdCamera->GetVideoStreamFrameBuffer(m_hTrackedCamera,
		vr::VRTrackedCameraFrameType_Undistorted, m_pCameraFrameBuffer, m_nCameraFrameBufferSize,
		&frameHeader, sizeof(frameHeader));
	if (nCameraError != vr::VRTrackedCameraError_None) return false;
	m_nLastFrameSequence = frameHeader.nFrameSequence;
	return true;
}

bool UVRFrontCamera::InitializeWebcameraComponent()
{
	hmdCamera = vr::VRTrackedCamera();
	if (!hmdCamera)
	{
		UE_LOG(LogTemp, Error, TEXT("InitializeWebcameraComponent::InitializeComponent camera is NULL"));
		return false;
	}
	bool bHasCamera = false;
	vr::EVRTrackedCameraError nCameraError = hmdCamera->HasCamera(vr::k_unTrackedDeviceIndex_Hmd, &bHasCamera);
	if (nCameraError != vr::VRTrackedCameraError_None || !bHasCamera)
	{
		UE_LOG(LogTemp, Error, TEXT("InitializeWebcameraComponent::No Tracked Camera Available!\n"));
		return false;
	}
	vr::ETrackedPropertyError propertyError;
	char buffer[128];
	auto system = vr::VRSystem();
	system->GetStringTrackedDeviceProperty(vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_CameraFirmwareDescription_String, buffer, sizeof(buffer), &propertyError);
	if (propertyError != vr::TrackedProp_Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitializeWebcameraComponent::InitializeComponent Failed to get tracked camera firmware description!\n"));
		return false;
	}
	FString bufferString = FString(ANSI_TO_TCHAR(buffer));
	auto name = UHeadMountedDisplayFunctionLibrary::GetHMDDeviceName();
	return true;
}

