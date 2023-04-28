// Fill out your copyright notice in the Description page of Project Settings.

#include "PerfectGymBlueprintLibrary.h"

#include "Engine.h"

#include "GameFramework/PlayerController.h"
#include "Engine/GameInstance.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/OnlineSession.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameSession.h"
#include "Net/OnlineEngineInterface.h"

#include "Engine/LevelStreamingDynamic.h"
#include "Engine/LevelStreaming.h"
#include "Engine/World.h"
//#include "ISteamVRPlugin.h" ---to
#include "Engine/Texture2D.h"
#include "RenderUtils.h"
#include "IXRTrackingSystem.h"
#include "IHeadMountedDisplay.h"

#include "PGPlayerController.h"

#include <Runtime/HeadMountedDisplay/Public/IHeadMountedDisplay.h> // for GetHmdType
#include <Runtime/HeadMountedDisplay/Public/IXRTrackingSystem.h> // for GetHmdType


void UPerfectGymBlueprintLibrary::SteamVRHMDProximitySensor(bool &covered)
{
	covered = false;
	//vr::IVRSystem * VRSystem = ISteamVRPlugin::Get().GetVRSystem(); ---to
	//level = VRSystem->GetTrackedDeviceActivityLevel(vr::k_unTrackedDeviceIndex_Hmd);
	//auto compositor = vr::VRCompositor(); ---to
	//vr::VRControllerState_t::ulButtonPressed
	//vr::VRControllerState_t state; ---to
	//VRSystem->GetControllerState(0, &state, sizeof(state)); ---to
	//int level = state.ulButtonPressed & (1UL << ((int)vr::EVRButtonId::k_EButton_ProximitySensor)); ---to
	//if (level != 0) ---to
	//{ ---to
	//	covered = true; ---to
	//} ---to
}

void UPerfectGymBlueprintLibrary::ClientTravelToSession(APlayerController* InPC, ETravelType InTravelType)
{
	UWorld* World = InPC->GetWorld();

	FString URL;
	if (UOnlineEngineInterface::Get()->GetResolvedConnectString(World, GameSessionName, URL))
	{
		if (InPC)
		{
			URL = World->RemovePIEPrefix(URL);
			InPC->ClientTravel(URL, InTravelType, InTravelType == ETravelType::TRAVEL_Relative ? true : false);
		}
		else
		{
			//UE_LOG(LogGame, Warning, TEXT("Failed to find local player for controller id %d"), InPC->GetLocalPlayer()->GetControllerId());
		}
	}
	else
	{
		//UE_LOG(LogGame, Warning, TEXT("Failed to resolve session connect string for %s"));
	}
}

void UPerfectGymBlueprintLibrary::GetActorsOfClassFromStreamedLevel(ULevelStreamingDynamic* InLevel, TSubclassOf<AActor> ActorClass, TArray<AActor*>& OutFoundActors)
{
	OutFoundActors.Reset();

	if (InLevel)
	{
		if (ULevel* LoadedLevel = InLevel->GetLoadedLevel())
		{
			GetActorsOfClassFromULevel(LoadedLevel, ActorClass, OutFoundActors);
		}
	}
}

void UPerfectGymBlueprintLibrary::GetActorsOfClassFromULevel(ULevel* InLevel, TSubclassOf<AActor> ActorClass, TArray<AActor*>& OutFoundActors)
{
	OutFoundActors.Reset();
	if (InLevel)
	{
		const TArray<AActor*>& LevelActors = InLevel->Actors;
		for (int32 i = 0; i < LevelActors.Num(); ++i)
		{
			AActor* LevelActor = LevelActors[i];

			if (LevelActor->IsA(ActorClass))
			{
				OutFoundActors.Add(LevelActor);
			}
		}
	}
}

AActor* UPerfectGymBlueprintLibrary::SpawnActorIntoLevel(UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, ULevelStreaming* Level, FVector Location, FRotator Rotation)
{
	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	if (!World)
	{
		return nullptr;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.OverrideLevel = Level->GetLoadedLevel();

	return World->SpawnActor(ActorClass, &Location, &Rotation, SpawnParameters);
}

void UPerfectGymBlueprintLibrary::RerunActorConstructionScripts(AActor* InActor)
{
	if (InActor)
	{
		InActor->RerunConstructionScripts();
	}
}

void UPerfectGymBlueprintLibrary::AddActorToTravelList(APlayerController* InPC, AActor* InActor)
{
	if (APGPlayerController* PGPC = Cast<APGPlayerController>(InPC))
	{
		PGPC->AddActorToTravelList(InActor);
	}
}

void UPerfectGymBlueprintLibrary::GetSortedPlayerScores(int32 InPlayerId, const TArray<int32>& InPlayerPoints, const TArray<int32>& InPlayerIds, TArray<int32>& OutSortedPlayerPoints, TArray<int32>& OutSortedPlayerIds)
{
	ensure(InPlayerPoints.Num() == InPlayerIds.Num());

	OutSortedPlayerPoints.Reset();
	OutSortedPlayerIds.Reset();

	TArray<TPair<int32, int32>> PlayerPoints; //X points, Y id
	for (int32 i = 0; i < InPlayerPoints.Num(); ++i)
	{
		PlayerPoints.Add(TPair<int32, int32>(InPlayerPoints[i], InPlayerIds[i]));
	}

	PlayerPoints.Sort([](const TPair<int32, int32>& Left, const TPair<int32, int32>& Right) 
	{
		return Left.Key > Right.Key;
	});

	for (int32 i = 0; i < PlayerPoints.Num(); ++i)
	{
		OutSortedPlayerPoints.Add(PlayerPoints[i].Key);
		OutSortedPlayerIds.Add(PlayerPoints[i].Value);
	}
}

void UPerfectGymBlueprintLibrary::SortLevelLists(const TArray<FBackendLevelStruct>& inLevels, EBackendSortingCriteria sortingCriteria, bool isAscending, TArray<FBackendLevelStruct>& outLevels)
{
	outLevels = inLevels;
	switch (sortingCriteria)
	{
		case EBackendSortingCriteria::CreatedBy:
		{
			outLevels.Sort([](const FBackendLevelStruct& a, const FBackendLevelStruct& b) {return a.levelAuthor > b.levelAuthor; });
			break;
		}
		case EBackendSortingCriteria::Difficulty:
		{
			outLevels.Sort([](const FBackendLevelStruct& a, const FBackendLevelStruct& b) {return a.difficultyLevel > b.difficultyLevel; });
			break;
		}
		case EBackendSortingCriteria::IsLevelSuggested:
		{
			outLevels.Sort([](const FBackendLevelStruct& a, const FBackendLevelStruct& b) {return a.isRecommended > b.isRecommended; });
			break;
		}
		case EBackendSortingCriteria::ScoredBudgets:
		{
			//outLevels.Sort([](const FBackendLevelStruct& a, const FBackendLevelStruct& b) {return a. > b.levelAuthor; });
			break;
		}
		case EBackendSortingCriteria::SongName:
		{
			outLevels.Sort([](const FBackendLevelStruct& a, const FBackendLevelStruct& b) {return a.songData.title > b.songData.title; });
			break;
		}
		case EBackendSortingCriteria::TimeOfLevel:
		{
			outLevels.Sort([](const FBackendLevelStruct& a, const FBackendLevelStruct& b) {return a.levelLengthInSec > b.levelLengthInSec; });
			break;
		}
	}
	if (!isAscending)
		Algo::Reverse(outLevels);
}

void UPerfectGymBlueprintLibrary::SortPlaylists(const TArray<FBackendPlaylist>& inPlaylists, EBackendSortingCriteria sortingCriteria, bool isAscending, TArray<FBackendPlaylist>& outPlaylists)
{
	outPlaylists = inPlaylists;
	switch (sortingCriteria)
	{
		case EBackendSortingCriteria::DateOfCreation:
		{
			outPlaylists.Sort([](const FBackendPlaylist& a, const FBackendPlaylist& b) {return a.createdDateInUtc > b.createdDateInUtc; });
			break;
		}
		case EBackendSortingCriteria::DateOfLastPlayed:
		{
			outPlaylists.Sort([](const FBackendPlaylist& a, const FBackendPlaylist& b) {return a.lastPlayedDateInUtc > b.lastPlayedDateInUtc; });
			break;
		}
		case EBackendSortingCriteria::PlaylistName:
		{
			outPlaylists.Sort([](const FBackendPlaylist& a, const FBackendPlaylist& b) {return a.name > b.name; });
			break;
		}
		case EBackendSortingCriteria::PlaylistTimeDuration:
		{
			outPlaylists.Sort([](const FBackendPlaylist& a, const FBackendPlaylist& b) {return a.durationInSeconds > b.durationInSeconds; });
			break;
		}
		case EBackendSortingCriteria::SongsCount:
		{
			outPlaylists.Sort([](const FBackendPlaylist& a, const FBackendPlaylist& b) {return a.levelGuids.Num() > b.levelGuids.Num(); });
			break;
		}
	}
	if (!isAscending)
		Algo::Reverse(outPlaylists);
}

void UPerfectGymBlueprintLibrary::RemoveAtString(const FString & string, FString& outString, int index)
{
	outString = string;
	if (index < 0 || index >= string.Len()) return;
	outString.RemoveAt(index);
}

bool UPerfectGymBlueprintLibrary::FileSaveString(FString SaveTextB, FString FileNameB)
{
	return FFileHelper::SaveStringToFile(SaveTextB, *(FPaths::GameDir() + FileNameB), FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

void UPerfectGymBlueprintLibrary::GetParametersFromURL(const FString& url, TMap<FString,FString> &paramsMap)
{
	TArray<FString> StringElements;
	FString baseUrl, parameters;
	url.Split("#", &baseUrl, &parameters);
	int32 NumElems = parameters.ParseIntoArray(StringElements, TEXT("&"), true);
	check(NumElems == StringElements.Num());
	TMap<FString, FString> urlParameters;
	FString ParamValDelimiter(TEXT("="));
	for (int Idx = 0; Idx < NumElems; ++Idx)
	{
		FString Param, Value;
		if (StringElements[Idx].Split(ParamValDelimiter, &Param, &Value))
		{
			paramsMap.Add(Param,Value);
		}
	}
}

FString UPerfectGymBlueprintLibrary::GetCurrentLevelName_bp(AActor * actor)
{
	if (!actor) return FString();
	auto name = actor->GetLevel()->GetOuter()->GetName();
	return name;
}

void UPerfectGymBlueprintLibrary::FadeHMDToColor(float time, float r, float g, float b)
{
	auto compositor = vr::VRCompositor();
	if (!compositor) return;

	/*UTexture2D* text = nullptr;
	CreateOpenVRTexture_t(text);*/
	//compositor->SetSkyboxOverride()
	compositor->CompositorBringToFront();
	compositor->FadeToColor(time, r, g, b, 1.0);

}

void UPerfectGymBlueprintLibrary::RestoreHMDImage(float time)
{
	auto compositor = vr::VRCompositor();
	if (!compositor) return;
	compositor->FadeToColor(time, 0.0, 0.0, 0.0, 0.0);
	compositor->FadeGrid(time, false);
}

void UPerfectGymBlueprintLibrary::BringFront()
{
	auto compositor = vr::VRCompositor();
	if (!compositor) return;
	compositor->FadeToColor(1.0f, 0.0, 0.0, 0.0, 0.0);
	compositor->FadeGrid(1.0f, false);
}

void UPerfectGymBlueprintLibrary::BringBack()
{
	auto compositor = vr::VRCompositor();
	if (!compositor) return;
	compositor->CompositorBringToFront();
	compositor->FadeToColor(1.0f, 0.0, 0.0, 0.0, 0.0);
	compositor->FadeGrid(1.0f, true);
}

bool UPerfectGymBlueprintLibrary::SetSkyboxOverride_LatLong(UTexture2D * LatLongSkybox)
{
	EPixelFormat format = LatLongSkybox->GetPixelFormat();
	UE_LOG(LogTemp, Warning, TEXT("Pixel format is: %d"), format);

	if (!LatLongSkybox)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bad texture passed in to SetSkyBoxOverride"));
		return false;
	}

	vr::HmdError HmdErr;
	vr::IVRCompositor * VRCompositor = (vr::IVRCompositor*)vr::VR_GetGenericInterface(vr::IVRCompositor_Version, &HmdErr);

	if (!VRCompositor)
	{
		UE_LOG(LogTemp, Warning, TEXT("VR Compositor InterfaceErrorCode %i"), (int32)HmdErr);
		return false;
	}

	vr::Texture_t Texture;

	Texture = CreateOpenVRTexture_t(LatLongSkybox);

	vr::EVRCompositorError CompositorError;
	CompositorError = VRCompositor->SetSkyboxOverride(&Texture, 1);

	if (CompositorError != vr::VRCompositorError_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("VR Compositor Error %i"), (int32)CompositorError);
		return false;
	}

	return true;
}

void UPerfectGymBlueprintLibrary::RestoreSkybox()
{
	auto compositor = vr::VRCompositor();
	if (compositor != nullptr)
		compositor->ClearSkyboxOverride();
}

vr::Texture_t UPerfectGymBlueprintLibrary::CreateOpenVRTexture_t(UTexture * Texture)
{
	vr::Texture_t VRTexture;

	if (Texture)
		VRTexture.handle = Texture->Resource->TextureRHI->GetNativeResource();
	else
		VRTexture.handle = NULL;

#if PLATFORM_LINUX
#if STEAMVR_USE_VULKAN_RHI
	VRTexture.eType = vr::TextureType_Vulkan;
#else
	VRTexture.eType = vr::TextureType_OpenGL;
#endif
#else
	VRTexture.eType = vr::TextureType_DirectX;
#endif
	VRTexture.eColorSpace = vr::ColorSpace_Auto;

	return VRTexture;
}
