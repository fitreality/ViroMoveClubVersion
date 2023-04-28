// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/World.h"
#include "SafetyBlueprintLibrary.generated.h"

USTRUCT(BlueprintType)
struct FPlayAreaSetup
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> playAreaCorners;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector playAreaCenter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector playAreaForwardVector;
};

USTRUCT(BlueprintType)
struct FPlayAreaConfig
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D playAreaSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int numberOfPlayers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float offsetBetweenAreas;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxInOneDimmension;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool shouldForwardVectorBeDirectedToCenter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool shouldRecenter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool shouldReverse;
};

UCLASS()
class VIROMOVE_API USafetyBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintCallable, Category = "BlueprintLibrary")
	static bool CheckIfAnyOfPlayersIsCloseEnough(TArray<FTransform> playerTransforms, float warningDistance, float& minDistance);

	UFUNCTION(BlueprintCallable, Category = "BlueprintLibrary")
	static void SetupPlayAreasForPlayers(AActor* actor, FPlayAreaConfig config, TArray<FVector> chaperonCorners, TArray<FPlayAreaSetup> &areas);

	UFUNCTION(BlueprintCallable, Category = "BlueprintLibrary")
	static bool IsPointInsidePolygon(const FVector& InLocation, const TArray<FVector>& InPolygon);
};
