// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructures/Gameplay/GameplayTypes.h"
#include "GameStructures/Gear/GearTypes.h"
#include "OnlineSubsystemOculus.h"
#include "GameStructures/Statistics/StatsTypes.h"
#include "BackendCommunication/WebCommunicationBaseComponent.h"
#include "BackendCommunicationComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOculusToken, FString, token);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VIROMOVE_API UBackendCommunicationComponent : public UWebCommunicationBaseComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBackendCommunicationComponent();

	//-----------------Stations---------------------------------------------------------------------------------//
	UFUNCTION(BlueprintCallable, Category = "Backend-Stations")
		void AuthenticateStation(FCallbackBinding callbackBinding, FAuthenticationCodeStations Code, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Stations")
		void GetStationContext(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Stations")
		void StartSessionForGuest(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Stations")
		void EndStationSession(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	//-----------------Purchases---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-Purchases")
		void GetEnergyCoins(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Purchases")
		void GetOrderStatus(FCallbackBinding callbackBinding, FString guid, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Purchases")
		void BuyNowWithEnergyCoins(FCallbackBinding callbackBinding, FBackendBuyEnergyCoins request, const TMap<FString, FString> &headers);

	//-----------------STATISTICS---------------------------------------------------------------------------------//
	UFUNCTION(BlueprintCallable, Category = "Backend-Statistics")
		void GetAllGamerStatistics(FCallbackBinding callbackBinding, FDateTime DateFrom, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Statistics")
		void GetGamerStatistics(FCallbackBinding callbackBinding, FDateTime LocalDateFrom, const TMap<FString, FString> &headers);

	//-----------------GamerInfo---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-GamerInfo")
		void GetGamerData(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-GamerInfo")
		void GetCareerModeLevels(FCallbackBinding callbackBinding, EBackendLevelType request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-GamerInfo")
		void SetMeasurementData(FCallbackBinding callbackBinding, FBackendMeasurementDataRequest request, const TMap<FString, FString> &headers);

	//---------------- Level ---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-Level")
		void BackendGetLevel(FCallbackBinding callbackBinding, FString Guid, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Level")
		void GetLevelsForFreeplay(FCallbackBinding callbackBinding, int PageSize, int Timestamp, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Level")
		void GetLevelsByAvailability(FCallbackBinding callbackBinding, EGameType LevelAvailability, int Timestamp, const TMap<FString, FString> &headers);

	//---------------- Settings ---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-Settings")
		void GetGameplaySettingsMultipliers(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Settings")
		void GetCountries(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Settings")
		FString BackendCreateLevelString(FCallbackBinding callbackBinding, FBackendLevelRequest request);

	//-----------------Gamer - Weapons ---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-GamerWeapon")
		void GetGamerWeapons(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-GamerWeapon")
		void GetGamerEquippedWeapons(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-GamerWeapon")
		void EquipWeapon(FCallbackBinding callbackBinding, FBackendEquipWeapon request, const TMap<FString, FString> &headers);

	//-----------------FavouriteLevel---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-Favourite")
		void GetGamerFavouriteLevels(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Favourite")
		void RemoveGamerFavouriteLevel(FCallbackBinding callbackBinding, FBackendFavouriteLevel request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Favourite")
		void AddGamerFavouriteLevel(FCallbackBinding callbackBinding, FBackendFavouriteLevel request, const TMap<FString, FString> &headers);

	//-----------------Playlists---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-Playlist")
		void GetPlaylist(FCallbackBinding callbackBinding, FString Guid, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Playlist")
		void GetPlaylistsForAccount(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Playlist")
		void CreatePlaylist(FCallbackBinding callbackBinding, FBackendPlayListCreate request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Playlist")
		void UpdatePlaylist(FCallbackBinding callbackBinding, FBackendPlayListUpdate request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Playlist")
		void DeletePlaylist(FCallbackBinding callbackBinding, FBackendPlayListGuid request, const TMap<FString, FString> &headers);

	//-----------------Challenges---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-Challenges")
		void GetChallenge(FCallbackBinding callbackBinding, FString ChallengeGuid, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Challenges")
		void GetCurrentChallenge(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Challenges")
		void GetPastChallenges(FCallbackBinding callbackBinding, int PageNumber, int PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Challenges")
		void GetGamerLastChallengeContext(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Challenges")
		void ConfirmGamerChallengeResult(FCallbackBinding callbackBinding, FConfirmChallengeResult request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Challenges")
		void GetGamerChallengeLimits(FCallbackBinding callbackBinding, FString ChallengeGuid, const TMap<FString, FString> &headers);

	//-----------------StartGame / End Game ---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-StartGame")
		void StartCareerGame(FCallbackBinding callbackBinding, FBackendStartGames request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-StartGame")
		void StartFreeplayGame(FCallbackBinding callbackBinding, FBackendStartGamesFreeplay request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-StartGame")
		void StartExerciseGame(FCallbackBinding callbackBinding, FBackendStartGames request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-StartGame")
		void StartChallengeGame(FCallbackBinding callbackBinding, FBackendStartGamesChallenge request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-StartGame")
		void StartCustomTrainingGame(FCallbackBinding callbackBinding, FTrainingStartGame request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-EndGame")
		void EndCustomTrainingGame(FCallbackBinding callbackBinding, FEndCustomTrainingGame request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-EndGame")
		void EndGame(FCallbackBinding callbackBinding, FBackendLevelResultToSend request, const TMap<FString, FString> &headers);

	//-----------------Lootbox---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-Lootbox")
		void GetLootboxes(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Lootbox")
		void OpenLootbox(FCallbackBinding callbackBinding, FlootboxId request, const TMap<FString, FString> &headers);

	//-----------------Leaderboards---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-Leaderboards")
		void GetCareerLeaderboardByLevelType(FCallbackBinding callbackBinding, EBackendLevelType LevelType, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Leaderboards")
		void GetCareerLeaderboardByLevel(FCallbackBinding callbackBinding, FString LevelGuid, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Leaderboards")
		void GetFreeplayLeaderboardByLevel(FCallbackBinding callbackBinding, FString LevelGuid, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Leaderboards")
		void GetFreeplayLeaderboardByLevelAndCountry(FCallbackBinding callbackBinding, FString LevelGuid, FString CountryCode, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Leaderboards")
		void GetChallengeLeaderboardByChallengeAndLevel(FCallbackBinding callbackBinding, FString LevelGuid, FString ChallengeGuid, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Leaderboards")
		void GetChallengeLeaderboardByChallenge(FCallbackBinding callbackBinding, FString ChallengeGuid, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	//-----------------BestResults---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-Results")
		void GetGamerFreeplayBestLevelResults(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Results")
		void GetGamerCareerBestLevelResults(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Results")
		void GetGamerChallengeBestLevelResults(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Results")
		void GetGameResult(FCallbackBinding callbackBinding, FString gameGuid, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Results")
		void GetCustomTrainingGameResult(FCallbackBinding callbackBinding, FString gameGuid, const TMap<FString, FString> &headers);

	//-----------------Trainings---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-Results")
		void IsFitnessTrainingUnitAvailable(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Results")
		void GetTrainingDurationParams(FCallbackBinding callbackBinding, ETrainingGola trainingGola, int32 trainingValue, EtrainingIntervalDifficulty difficulty,  const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-Results")
		void GetTrainingModuleAvailability(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	//-----------------OCULUS---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-Oculus")
		void GetOculusAccessToken();

	UPROPERTY(BlueprintAssignable, Category = "Backend-Oculus")
		FOculusToken GetOculusToken;

	//-----------------UserSessions---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Backend-UserSession")
		void StartUserSessions(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Backend-UserSession")
		void EndUserSessions(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
