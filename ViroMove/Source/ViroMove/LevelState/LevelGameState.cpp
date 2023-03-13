// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGameState.h"
#include "Engine/LevelStreaming.h"
#include "Engine/World.h"
#include "Engine/LevelStreamingKismet.h"
#include "PerfectGym.h"
#include "UnrealNetwork.h"
#include "Engine.h"
#include "PackageName.h"

void ALevelGameState::StreamLevels(const TArray<TSoftObjectPtr<UWorld>>& Levels, const TArray<FVector>& Locations, const TArray<FRotator>& Rotaction)
{
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return;
	}

	PreviousLevels = LoadedLevels;
	LoadedLevels.Reset();
	NumLevelsLoaded = 0;

	bool bAllSuccess = true;
	ensure(LoadedLevels.Num() == 0);

	for (int32 i = 0; i < Levels.Num(); ++i)
	{
		if (Levels[i].GetAssetName().IsEmpty())
		{
			return;
		}

		bool bSuccess = false;
		ULevelStreamingDynamic* LoadedLevel = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(this, Levels[i], Locations[i], Rotaction[i], bSuccess);

		const FString& LongPackageName = Levels[i].GetLongPackageName();
		const FString ShortPackageName = FPackageName::GetShortName(LongPackageName);
		const FString PackagePath = FPackageName::GetLongPackagePath(LongPackageName);
		FString UniqueLevelPackageName = PackagePath + TEXT("/") + ShortPackageName;
		UniqueLevelPackageName = World->RemovePIEPrefix(UniqueLevelPackageName);

		LoadedLevel->SetWorldAssetByPackageName(FName(*UniqueLevelPackageName));

		if (bSuccess)
		{
			LoadedLevels.Add(LoadedLevel);
		}
		bAllSuccess &= bSuccess;
	}

	if (bAllSuccess)
	{
		if (OnLevelLoadedDelegateHandle.IsValid())
		{
			FWorldDelegates::LevelAddedToWorld.Remove(OnLevelLoadedDelegateHandle);
		}

	}
}

ULevelStreamingDynamic* ALevelGameState::StreamLevel(const TSoftObjectPtr<UWorld>& Level, const FVector& Locations, const FRotator& Rotaction)
{
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return nullptr;
	}

	PreviousLevels = LoadedLevels;
	LoadedLevels.Reset();
	NumLevelsLoaded = 0;

	bool bAllSuccess = true;
	ensure(LoadedLevels.Num() == 0);

	if (Level.GetAssetName().IsEmpty())
	{
		return nullptr;
	}

	bool bSuccess = false;
	ULevelStreamingDynamic* LoadedLevel = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(this, Level, Locations, Rotaction, bSuccess);

	const FString& LongPackageName = Level.GetLongPackageName();
	const FString ShortPackageName = FPackageName::GetShortName(LongPackageName);
	const FString PackagePath = FPackageName::GetLongPackagePath(LongPackageName);
	FString UniqueLevelPackageName = PackagePath + TEXT("/") + ShortPackageName;
	UniqueLevelPackageName = World->RemovePIEPrefix(UniqueLevelPackageName);

	LoadedLevel->SetWorldAssetByPackageName(FName(*UniqueLevelPackageName));

	if (bSuccess)
	{
		LoadedLevels.Add(LoadedLevel);
	}
	bAllSuccess &= bSuccess;

	if (bAllSuccess)
	{
		if (OnLevelLoadedDelegateHandle.IsValid())
		{
			FWorldDelegates::LevelAddedToWorld.Remove(OnLevelLoadedDelegateHandle);
		}
		return LoadedLevel;
	}
	else
	{
		return nullptr;
	}
}

void ALevelGameState::StreamSubLevels(const TArray<FName>& SubLevels, const TArray<FVector>& Locations)
{
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return;
	}

	bool bAllSuccess = true;

	for (int32 i = 0; i < SubLevels.Num(); ++i)
	{
		if (!SubLevels[i].IsValid())
		{
			return;
		}

		bool bSuccess = false;
		ULevelStreamingDynamic* LoadedLevel = ULevelStreamingDynamic::LoadLevelInstance(this, SubLevels[i].ToString(), Locations[i], FRotator(0.0f, 0.0f, 0.0f), bSuccess);
		LoadedLevel->SetWorldAssetByPackageName(SubLevels[i]);

		if (bSuccess)
		{
			LoadedLevels.Add(LoadedLevel);
		}
		bAllSuccess &= bSuccess;
	}
}

void ALevelGameState::UnloadLevels()
{
	for (int32 i = 0; i < LoadedLevels.Num(); ++i)
	{
		ULevelStreamingDynamic* LoadedLevel = LoadedLevels[i];
		LoadedLevel->SetIsRequestingUnloadAndRemoval(true);
	}

	LoadedLevels.Reset();
	NumLevelsLoaded = 0;
}

void ALevelGameState::UnloadLevel(ULevelStreamingDynamic* Level)
{
	Level->SetIsRequestingUnloadAndRemoval(true);
}

void ALevelGameState::OnLevelLoaded(ULevel* InLevel, UWorld* InWorld)
{
	bool bLevelIsValid = false;
	for (int32 i = 0; i < LoadedLevels.Num(); ++i)
	{
		if (InLevel == LoadedLevels[i]->GetLoadedLevel())
		{
			bLevelIsValid = true;
			break;
		}
	}

	if (bLevelIsValid)
	{
		NumLevelsLoaded++;
		if (NumLevelsLoaded >= LoadedLevels.Num())
		{
			if (UWorld* NewWorld = Cast<UWorld>(InLevel->GetOuter()))
			{
				if (NewWorld->GetStreamingLevels().Num() > 0)
				{
					TArray<FName> SubLevels;
					TArray<FVector> SubLevelsLocations;
					for (int32 i = 0; i < NewWorld->GetStreamingLevels().Num(); ++i)
					{
						FString AssetName = "";
						AssetName.Append(NewWorld->GetStreamingLevels()[i]->GetWorldAsset().GetLongPackageName());
						AssetName = NewWorld->RemovePIEPrefix(AssetName);
						SubLevels.Add(*AssetName);
						SubLevelsLocations.Add(FVector(0.0f, 0.0f, 0.0f));
					}

					StreamSubLevels(SubLevels, SubLevelsLocations);
					return;
				}
			}

			for (int32 i = 0; i < PreviousLevels.Num(); ++i)
			{
				ULevelStreamingDynamic* PreviousLevel = PreviousLevels[i];
				PreviousLevel->SetIsRequestingUnloadAndRemoval(true);
			}
		}
	}
}


