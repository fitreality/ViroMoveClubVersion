// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <memory>
#include <functional>
#include <string>
#include "AudioAnalyzer.generated.h"

class UInstancedStaticMeshComponent;
class UStaticMesh;



UCLASS()
class VIROMOVE_API AAudioAnalyzer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioAnalyzer();

	UFUNCTION(BlueprintCallable)
	void DrawWaveform(const FString& pathToWav, float widthFactor, float heightFactor);



	UFUNCTION(BlueprintCallable)
	void ClearInstances();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:


	UPROPERTY(EditAnywhere)
	USceneComponent* rootSceneComponent;

	UPROPERTY(EditAnywhere)
	UStaticMesh* meshToUse;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* meshFollower;

	UPROPERTY()
	UInstancedStaticMeshComponent* instances;
};
