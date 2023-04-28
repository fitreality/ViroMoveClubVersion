// Fill out your copyright notice in the Description page of Project Settings.

#include "SafetyActorComponent.h"

using namespace vr;
// Sets default values for this component's properties
USafetyActorComponent::USafetyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void USafetyActorComponent::GetChaperoneRectangle(FVector & v0, FVector & v1, FVector & v2, FVector & v3)
{
	auto chaperonePointer = vr::VRChaperone();
	if (chaperonePointer)
	{
		HmdQuad_t rectangle;
		float sizeX, sizeY;
		chaperonePointer->ReloadInfo();
		int maxIter = 10;
		int i = 0;
		while(!chaperonePointer->GetPlayAreaRect(&rectangle) && i++ < maxIter);
		bool b = chaperonePointer->GetPlayAreaRect(&rectangle);
		if (!b) return;
		chaperonePointer->GetPlayAreaSize(&sizeX, &sizeY);
		auto c0 = rectangle.vCorners[0];
		auto c1 = rectangle.vCorners[1];
		auto c2 = rectangle.vCorners[2];
		auto c3 = rectangle.vCorners[3];
		const float metersToCentimeters = 100;

		v0 = FVector(-c0.v[2], c0.v[0], c0.v[1]) * metersToCentimeters;
		v1 = FVector(-c1.v[2], c1.v[0], c1.v[1]) * metersToCentimeters;
		v2 = FVector(-c2.v[2], c2.v[0], c2.v[1]) * metersToCentimeters;
		v3 = FVector(-c3.v[2], c3.v[0], c3.v[1]) * metersToCentimeters;
		UE_LOG(LogTemp, Warning, TEXT("v0: %s"), *v0.ToString());
		UE_LOG(LogTemp, Warning, TEXT("v1: %s"), *v1.ToString());
		UE_LOG(LogTemp, Warning, TEXT("v2: %s"), *v2.ToString());
		UE_LOG(LogTemp, Warning, TEXT("v3: %s"), *v3.ToString());
		UE_LOG(LogTemp, Warning, TEXT("%f: %f"), sizeX, sizeY);
	}
}

// Called when the game starts
void USafetyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	EVRInitError eError;
	vr_pointer = nullptr;
	vr_pointer = vr::VR_Init(&eError, vr::VRApplication_Scene);
//	vr_pointer->Get
	if (eError != VRInitError_None)
	{
		vr_pointer = NULL;
		printf("Unable to init VR runtime: %s \n",
			VR_GetVRInitErrorAsEnglishDescription(eError));
		return;
	}
	if (!vr_pointer)
	{
		UE_LOG(LogTemp, Error, TEXT("USafetyActorComponent::BeginPlay - Error while initializing openvr"));
		return;
	}
}


// Called every frame
void USafetyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/*if (!vr_pointer)  return;
	FString info = "";
	for (unsigned int deviceId = 0; deviceId < k_unMaxTrackedDeviceCount; deviceId++) {

		TrackedDevicePose_t tr;
		ETrackedDeviceClass cl = vr_pointer->GetTrackedDeviceClass(deviceId);
		if (!vr_pointer->IsTrackedDeviceConnected(deviceId))
		{
			continue;
		}
		if (cl == ETrackedDeviceClass::TrackedDeviceClass_HMD)
		{
			vr_pointer->GetDeviceToAbsoluteTrackingPose(TrackingUniverseStanding, 0, &tr, 1);
			auto m1 = vr_pointer->GetRawZeroPoseToStandingAbsoluteTrackingPose();
			auto m = tr.mDeviceToAbsoluteTracking;

			float x1 = m1.m[0][3];
			float y1 = m1.m[1][3];
			float z1 = m1.m[2][3];
			FVector vec_offset(x1, y1, z1);

			float x = m.m[0][3];
			float y = m.m[1][3];
			float z = m.m[2][3];
			FVector vec(x, y, z);

			info.Append("HMD: ");
			info.Append(FString::FromInt(deviceId));
			info.Append(", ");
			info.Append(vec.ToString());
			info.Append(" - offset: ");
			info.Append(vec_offset.ToString());
			info.Append("\n");
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *info);*/
}

