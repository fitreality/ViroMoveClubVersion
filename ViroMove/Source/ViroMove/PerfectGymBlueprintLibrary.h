// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <Runtime/Engine/Classes/Engine/EngineBaseTypes.h>
#include <Runtime/Engine/Classes/GameFramework/Actor.h>
#include "GameStructures/Gameplay/GameplayTypes.h"
#include "openvr.h"
#include "PerfectGymBlueprintLibrary.generated.h"
class AActor;
class UTexture;
class UTexture2D;
class APlayerController;
class ULevelStreamingDynamic;
class ALevelScriptActor;
class ULevelStreaming;


UCLASS()
class VIROMOVE_API UPerfectGymBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "BlueprintLibrary")
	static void SteamVRHMDProximitySensor(bool &covered);

	UFUNCTION(BlueprintCallable, Category = "BlueprintLibrary")
	static void ClientTravelToSession(APlayerController* InPC, ETravelType InTravelType);

	UFUNCTION(BlueprintCallable, Category = "BlueprintLibrary")
	static void GetActorsOfClassFromStreamedLevel(ULevelStreamingDynamic* InLevel, TSubclassOf<AActor> ActorClass, TArray<AActor*>& OutFoundActors);

	UFUNCTION(BlueprintCallable, Category = "BlueprintLibrary")
	static void GetActorsOfClassFromULevel(ULevel* InLevel, TSubclassOf<AActor> ActorClass, TArray<AActor*>& OutFoundActors);

	UFUNCTION(BlueprintCallable, Category = "BlueprintLibrary", meta = (WorldContext = "WorldContextObject"))
	static AActor* SpawnActorIntoLevel(UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, ULevelStreaming* Level, FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = "BlueprintLibrary")
	static void RerunActorConstructionScripts(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "BlueprintLibrary")
	static void AddActorToTravelList(APlayerController* InPC, AActor* InActor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Multiplayer|Score")
	static void GetSortedPlayerScores(int32 InPlayerId, const TArray<int32>& InPlayerPoints, const TArray<int32>& InPlayerIds, TArray<int32>& OutSortedPlayerPoints, TArray<int32>& OutSortedPlayerIds);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sorting|Levels")
	static void SortLevelLists(const TArray<FBackendLevelStruct>& inLevels, EBackendSortingCriteria sortingCriteria, bool isAscending, TArray<FBackendLevelStruct>& outLevels);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sorting|Playlists")
	static void SortPlaylists(const TArray<FBackendPlaylist>& inPlaylists, EBackendSortingCriteria sortingCriteria, bool isAscending, TArray<FBackendPlaylist>& outPlaylists);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Sorting|Playlists")
	static void RemoveAtString(const FString &string, FString& outString, int index);

	UFUNCTION(BlueprintCallable, Category = "Save")
	static bool FileSaveString(FString SaveTextB, FString FileNameB);

	UFUNCTION(BlueprintCallable, Category = "URL")
	static void GetParametersFromURL(const FString& url, TMap<FString, FString>& paramsMap);

	UFUNCTION(BlueprintCallable)
		static FString GetCurrentLevelName_bp(AActor* actor);

	UFUNCTION(BlueprintCallable)
		static void FadeHMDToColor(float time, float r, float g, float b);
	UFUNCTION(BlueprintCallable)
		static void RestoreHMDImage(float time);

	UFUNCTION(BlueprintCallable)
		static void BringFront();
	UFUNCTION(BlueprintCallable)
		static void BringBack();

	UFUNCTION(BlueprintCallable)
		static bool SetSkyboxOverride_LatLong(UTexture2D * LatLongSkybox);

	UFUNCTION(BlueprintCallable)
		static void RestoreSkybox();

private:
	static vr::Texture_t CreateOpenVRTexture_t(UTexture * Texture);
};
