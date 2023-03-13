// Fill out your copyright notice in the Description page of Project Settings.

#include "VRFrontCameraRenderer.h"
#include "VRFrontCamera/VRFrontCamera.h"
#include "MaterialShared.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include <Runtime/Engine/Classes/Engine/Texture2D.h>

// Sets default values
AVRFrontCameraRenderer::AVRFrontCameraRenderer()
{
	PrimaryActorTick.bCanEverTick = true;
	InitializeMaterials();
	cameraComponent = CreateDefaultSubobject<UVRFrontCamera>("CameraComponent");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;
}

// Called when the game starts or when spawned
void AVRFrontCameraRenderer::BeginPlay()
{
	Super::BeginPlay();
	MaterialInstance = UMaterialInstanceDynamic::Create(CameraFrameMaterial, this);
	mesh->SetMaterial(0, MaterialInstance);	
}

// Called every frame
void AVRFrontCameraRenderer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto cameraFrame = cameraComponent->GetCameraFrame();
	if (cameraFrame)
		MaterialInstance->SetTextureParameterValue("CameraFrame", cameraComponent->GetCameraFrame());
}

void AVRFrontCameraRenderer::InitializeMaterials()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		TranslucentMaterial_Finder(TEXT("Material'/Game/MarcinNiedabylski/Materials/CameraFrameMaterial.CameraFrameMaterial'"));
	CameraFrameMaterial = TranslucentMaterial_Finder.Object;
}

