// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "PerfectGymTypes.generated.h"

class UWorld;
class UTextureCube;

USTRUCT(BlueprintType)
struct FPortalConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureCube* LevelCubemap;
};

UENUM(BlueprintType)
enum class EPortalType : uint8
{
	Dynamic,
	Start,
	End,
	MAX
};

USTRUCT(BlueprintType)
struct FLevelReference
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> Level;

	friend FArchive& operator<<(FArchive& Ar, FLevelReference& LevelRef)
	{
		LevelRef.Serialize(Ar);
		return Ar;
	}

	bool Serialize(FArchive& Ar)
	{
		FSoftObjectPath LevelSoftObjectPath = Level.ToSoftObjectPath();
		Ar << LevelSoftObjectPath;
		if (Ar.IsLoading())
		{
			Level = LevelSoftObjectPath;
		}

		return true;
	}
};
