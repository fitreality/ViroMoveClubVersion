// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VRFrontCameraRenderer.generated.h"

class UVRFrontCamera;
class UStaticMeshComponent;
class UMaterialInterface;

UCLASS()
class VIROMOVE_API AVRFrontCameraRenderer : public AActor
{
	GENERATED_BODY()
	
public:	
	AVRFrontCameraRenderer();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	void InitializeMaterials();

	UPROPERTY()
		UVRFrontCamera * cameraComponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent *mesh;

	UPROPERTY()
		UMaterialInterface* CameraFrameMaterial;

	UPROPERTY()
		UMaterialInterface* OpaqueMaterial_OneSided;

	UPROPERTY(Transient, DuplicateTransient)
		UMaterialInstanceDynamic* MaterialInstance;
	
};
