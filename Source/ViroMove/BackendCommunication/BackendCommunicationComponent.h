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

	UFUNCTION(BlueprintCallable, Category = "Ihrsa")
		void GetCountries(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	//-----------------Ihrsa---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Ihrsa")
		void GetActiveUser(FCallbackBinding callbackBinding, FString stationGuid, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Ihrsa")
		void RemoveActiveUser(FRemoveUser stationGuid, const TMap<FString, FString> &headers);

	//Response type: leaderboardPosition
	UFUNCTION(BlueprintCallable, Category = "Ihrsa")
		void FitnessGameSummary(FCallbackBinding callbackBinding, FFitnessGameSummary request, const TMap<FString, FString> &headers);

	//-----------------ACCOUNT---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Account")
		void SetMeasurementData(FCallbackBinding callbackBinding, FBackendMeasurementDataRequest request, const TMap<FString, FString> &headers);



	//-----------------BestResults---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "BestResults")
		void GetGamerFreeplayBestLevelResults(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "BestResults")
		void GetGamerCareerBestLevelResults(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "BestResults")
		void GetGamerChallengeBestLevelResults(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);


	//-----------------Level---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Level")
		void BackendCreateLevel(FCallbackBinding callbackBinding, FBackendLevelRequest request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Level")
		FString BackendCreateLevelString(FCallbackBinding callbackBinding, FBackendLevelRequest request);

	UFUNCTION(BlueprintCallable, Category = "Level")
		void BackendUpdateLevel(FCallbackBinding callbackBinding, FBackendLevelRequest request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Level")
		void GetCareerModeLevels(FCallbackBinding callbackBinding, EBackendLevelType request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Level")
		void BackendGetLevel(FCallbackBinding callbackBinding, FString Guid, const TMap<FString, FString> &headers);


	UFUNCTION(BlueprintCallable, Category = "Level")
		void GetLevelsForFreeplay(FCallbackBinding callbackBinding, int PageSize, int Timestamp, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Level")
		void GetGamerFavouriteLevels(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Level")
		void RemoveGamerFavouriteLevel(FCallbackBinding callbackBinding, FBackendFavouriteLevel request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Level")
		void AddGamerFavouriteLevel(FCallbackBinding callbackBinding, FBackendFavouriteLevel request, const TMap<FString, FString> &headers);


	//-----------------STATISTICS---------------------------------------------------------------------------------//
	UFUNCTION(BlueprintCallable, Category = "STATISTICS")
		void GetAllGamerStatistics(FCallbackBinding callbackBinding, FDateTime DateFrom, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "STATISTICS")
		void GetGamerStatistics(FCallbackBinding callbackBinding, FDateTime LocalDateFrom, const TMap<FString, FString> &headers);


	//-----------------Playlists---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Playlists")
		void GetPlaylist(FCallbackBinding callbackBinding, FString Guid, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Playlists")
		void GetPlaylistsForAccount(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Playlists")
		void CreatePlaylist(FCallbackBinding callbackBinding, FBackendPlayListCreate request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Playlists")
		void UpdatePlaylist(FCallbackBinding callbackBinding, FBackendPlayListUpdate request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Playlists")
		void DeletePlaylist(FCallbackBinding callbackBinding, FBackendPlayListGuid request, const TMap<FString, FString> &headers);


	//-----------------SCORE---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "SCORE")
		void GetGameplaySettingsMultipliers(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);


	//-----------------Challenges---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Challenges")
		void GetChallenge(FCallbackBinding callbackBinding, FString ChallengeGuid, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Challenges")
		void GetCurrentChallenge(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Challenges")
		void GetPastChallenges(FCallbackBinding callbackBinding, int PageNumber, int PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Challenges")
		void GetGamerLastChallengeContext(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Challenges")
		void ConfirmGamerChallengeResult(FCallbackBinding callbackBinding, FConfirmChallengeResult request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Challenges")
		void GetGamerChallengeLimits(FCallbackBinding callbackBinding, FString ChallengeGuid, const TMap<FString, FString> &headers);

	//-----------------Games---------------------------------------------------------------------------------//


	UFUNCTION(BlueprintCallable, Category = "Games")
		void StartCareerGame(FCallbackBinding callbackBinding, FBackendStartGames request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Games")
		void StartFreeplayGame(FCallbackBinding callbackBinding, FBackendStartGamesFreeplay request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Games")
		void StartExerciseGame(FCallbackBinding callbackBinding, FBackendStartGames request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Games")
		void StartChallengeGame(FCallbackBinding callbackBinding, FBackendStartGamesChallenge request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Games")
		void EndGame(FCallbackBinding callbackBinding, FBackendLevelResultToSend request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Games")
		void GetGameResult(FCallbackBinding callbackBinding, FString gameGuid, const TMap<FString, FString> &headers);


	//-----------------Gamers---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Gamers")
		void GetGamerData(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamers")
		void GetGamerWeapons(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamers")
		void GetGamerEquippedWeapons(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamers")
		void EquipWeapon(FCallbackBinding callbackBinding, FBackendEquipWeapon request, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamers")
		void GetLootboxes(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Gamers")
		void OpenLootbox(FCallbackBinding callbackBinding, FlootboxId request, const TMap<FString, FString> &headers);
	//-----------------Leaderboards---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Leaderboards")
		void GetCareerLeaderboardByLevelType(FCallbackBinding callbackBinding, EBackendLevelType LevelType, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Leaderboards")
		void GetCareerLeaderboardByLevel(FCallbackBinding callbackBinding, FString LevelGuid, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Leaderboards")
		void GetFreeplayLeaderboardByLevel(FCallbackBinding callbackBinding, FString LevelGuid, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Leaderboards")
		void GetFreeplayLeaderboardByLevelAndCountry(FCallbackBinding callbackBinding, FString LevelGuid, FString CountryCode, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Leaderboards")
		void GetChallengeLeaderboardByChallengeAndLevel(FCallbackBinding callbackBinding, FString LevelGuid, FString ChallengeGuid, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Leaderboards")
		void GetChallengeLeaderboardByChallenge(FCallbackBinding callbackBinding, FString ChallengeGuid, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers);


	//-----------------Purchases---------------------------------------------------------------------------------//


	UFUNCTION(BlueprintCallable, Category = "Gamers")
		void GetEnergyCoins(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Games")
		void GetOrderStatus(FCallbackBinding callbackBinding, FString guid, const TMap<FString, FString> &headers);

	UFUNCTION(BlueprintCallable, Category = "Games")
		void BuyNowWithEnergyCoins(FCallbackBinding callbackBinding, FBackendBuyEnergyCoins request, const TMap<FString, FString> &headers);


	//-----------------OCULUS---------------------------------------------------------------------------------//
	UFUNCTION(BlueprintCallable, Category = "OCULUS")
		void GetOculusAccessToken();

	UPROPERTY(BlueprintAssignable, Category = "OCULUS")
		FOculusToken GetOculusToken;

	//-----------------UserSessions---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "UserSessions")
		void StartUserSessions(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);


	UFUNCTION(BlueprintCallable, Category = "UserSessions")
		void EndUserSessions(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
