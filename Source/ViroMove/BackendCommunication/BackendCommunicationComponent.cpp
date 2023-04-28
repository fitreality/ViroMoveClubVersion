// Fill out your copyright notice in the Description page of Project Settings.

#include "BackendCommunicationComponent.h"
#include "OnlineSubsystemOculus.h"
#include "GameStructures/Leaderboards/LeaderboardTypes.h"

////--------HTTP & JSON includes--------
//#include "Runtime/Json/Public/Dom/JsonObject.h"
//#include "Runtime/Json/Public/Serialization/JsonReader.h"
//#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
//#include "JsonObjectConverter.h"

// Sets default values for this component's properties
UBackendCommunicationComponent::UBackendCommunicationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

}


// Called when the game starts
void UBackendCommunicationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UBackendCommunicationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//-----------------Ihrsa---------------------------------------------------------------------------------//


void UBackendCommunicationComponent::GetCountries(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FCountriesList"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Countries/GetCountries", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FCountriesList>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetActiveUser(FCallbackBinding callbackBinding, FString stationGuid, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FActiveUser"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("GameManagement/GetActiveUser?StationGuid=" + stationGuid, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FActiveUser>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::RemoveActiveUser(FRemoveUser request, const TMap<FString, FString> &headers)
{
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FRemoveUser>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("GameManagement/RemoveActiveUser", ContentJsonString, headers);
	Request->OnProcessRequestComplete();
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::FitnessGameSummary(FCallbackBinding callbackBinding, FFitnessGameSummary request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FleaderboardPosition"))
		return;
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FFitnessGameSummary>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("GameManagement/FitnessGameSummary", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FleaderboardPosition>, callbackBinding);
	Request->ProcessRequest();
}

//-----------------ACCOUNT---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::SetMeasurementData(FCallbackBinding callbackBinding, FBackendMeasurementDataRequest request, const TMap<FString, FString> &headers) {
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendMeasurementDataRequest>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Account/SetMeasurementData", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}

//-----------------BestResults---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::GetGamerFreeplayBestLevelResults(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendBestResults"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("BestResults/GetGamerFreeplayBestLevelResults", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendBestResults>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::GetGamerCareerBestLevelResults(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendBestResults"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("BestResults/GetGamerCareerBestLevelResults", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendBestResults>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::GetGamerChallengeBestLevelResults(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendBestResults"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("BestResults/GetGamerChallengeBestLevelResults", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendBestResults>, callbackBinding);
	Request->ProcessRequest();
}


//-----------------Level---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::BackendCreateLevel(FCallbackBinding callbackBinding, FBackendLevelRequest request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendLevelResponses"))
		return;
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendLevelRequest>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Levels/CreateLevel", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBackendLevelResponses>, callbackBinding);
	Request->ProcessRequest();
}

FString UBackendCommunicationComponent::BackendCreateLevelString(FCallbackBinding callbackBinding, FBackendLevelRequest request)
{
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendLevelRequest>(request, ContentJsonString);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ContentJsonString);
	return ContentJsonString;

}

void UBackendCommunicationComponent::BackendUpdateLevel(FCallbackBinding callbackBinding, FBackendLevelRequest request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendLevelResponses"))
		return;
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendLevelRequest>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Levels/UpdateLevel", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBackendLevelResponses>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::GetCareerModeLevels(FCallbackBinding callbackBinding, EBackendLevelType Type, const TMap<FString, FString> &headers) {
	FString SEnum;
	switch (Type) {
	case EBackendLevelType::Boxing: SEnum = "Boxing";
		break;
	case EBackendLevelType::Shooting: SEnum = "Shooting";
		break;
	case EBackendLevelType::Swording: SEnum = "Swording";
		break;
	case EBackendLevelType::WeaponMastery: SEnum = "WeaponMastery";
		break;
	case EBackendLevelType::Exercising: SEnum = "Exercising";
		break;
	}
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FCareerLevelsResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Levels/GetCareerModeLevels?LevelType=" + SEnum, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FCareerLevelsResponse>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::BackendGetLevel(FCallbackBinding callbackBinding, FString Guid, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendLevelRequest"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Levels/GetLevel?Guid=" + Guid, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendLevelRequest>, callbackBinding);
	Request->ProcessRequest();
}


UFUNCTION(BlueprintCallable, Category = "Level")
void UBackendCommunicationComponent::GetLevelsForFreeplay(FCallbackBinding callbackBinding, int PageSize, int Timestamp, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendGetLevelsByTimestampResponse"))
		return;
	FString URLRequest = "Levels/GetLevelsForFreeplay?PageSize=" + FString::FromInt(PageSize);
	URLRequest += "&Timestamp=" + FString::FromInt(Timestamp);
	TSharedRef<IHttpRequest> Request = GetRequest(URLRequest, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendGetLevelsByTimestampResponse>, callbackBinding);
	Request->ProcessRequest();
}


UFUNCTION(BlueprintCallable, Category = "Level")
void UBackendCommunicationComponent::GetGamerFavouriteLevels(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendGetFavouriteLevel"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Levels/GetGamerFavouriteLevels", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendGetFavouriteLevel>, callbackBinding);
	Request->ProcessRequest();
}

UFUNCTION(BlueprintCallable, Category = "Level")
void UBackendCommunicationComponent::AddGamerFavouriteLevel(FCallbackBinding callbackBinding, FBackendFavouriteLevel request, const TMap<FString, FString> &headers) {
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendFavouriteLevel>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Levels/AddGamerFavouriteLevel", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}

UFUNCTION(BlueprintCallable, Category = "Level")
void UBackendCommunicationComponent::RemoveGamerFavouriteLevel(FCallbackBinding callbackBinding, FBackendFavouriteLevel request, const TMap<FString, FString> &headers) {
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendFavouriteLevel>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Levels/RemoveGamerFavouriteLevel", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}


//-----------------Playlists---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::GetPlaylist(FCallbackBinding callbackBinding, FString Guid, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendPlayListResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Playlists/GetPlaylist?PlaylistGuid=" + Guid, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendPlayListResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetPlaylistsForAccount(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendPlayListsResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Playlists/GetPlaylistsForAccount", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendPlayListsResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::CreatePlaylist(FCallbackBinding callbackBinding, FBackendPlayListCreate request, const TMap<FString, FString> &headers) {
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendPlayListCreate>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Playlists/CreatePlaylist", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::UpdatePlaylist(FCallbackBinding callbackBinding, FBackendPlayListUpdate request, const TMap<FString, FString> &headers) {
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendPlayListUpdate>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Playlists/UpdatePlaylist", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::DeletePlaylist(FCallbackBinding callbackBinding, FBackendPlayListGuid request, const TMap<FString, FString> &headers) {
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendPlayListGuid>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Playlists/DeletePlaylist", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}

//-----------------Challenges---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::GetChallenge(FCallbackBinding callbackBinding, FString ChallengeGuid, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FChallengeResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Challenges/GetChallenge?ChallengeGuid=" + ChallengeGuid, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FChallengeResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetCurrentChallenge(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FCurrentChallengeResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Challenges/GetCurrentChallenge", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FCurrentChallengeResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetPastChallenges(FCallbackBinding callbackBinding, int PageNumber, int PageSize, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FPastChallengeResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Challenges/GetPastChallenges?PageNumber=" + FString::FromInt(PageNumber) + "&PageSize=" + FString::FromInt(PageSize), headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FPastChallengeResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetGamerLastChallengeContext(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGamerLastChallengeContext"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Challenges/GetGamerLastChallengeContext", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FGamerLastChallengeContext>, callbackBinding);
	Request->ProcessRequest();
}
void UBackendCommunicationComponent::ConfirmGamerChallengeResult(FCallbackBinding callbackBinding, FConfirmChallengeResult request, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FConfirmChallengeResults"))
		return;
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FConfirmChallengeResult>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Challenges/ConfirmGamerChallengeResult", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FConfirmChallengeResults>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetGamerChallengeLimits(FCallbackBinding callbackBinding, FString ChallengeGuid, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FChallengeLimitsResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Challenges/GetGamerChallengeLimits?ChallengeGuid=" + ChallengeGuid, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FChallengeLimitsResponse>, callbackBinding);
	Request->ProcessRequest();
}


//-----------------STATISTICS---------------------------------------------------------------------------------//
void UBackendCommunicationComponent::GetAllGamerStatistics(FCallbackBinding callbackBinding, FDateTime DateFrom, const TMap<FString, FString> &headers) {
	FString StartDate = DateFrom.ToIso8601();
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendStatisticResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Statistics/GetAllGamerStatistics?StartDate=" + StartDate, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBackendStatisticResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetGamerStatistics(FCallbackBinding callbackBinding, FDateTime LocalDateFrom, const TMap<FString, FString> &headers) {
	FString StartDate = LocalDateFrom.ToIso8601();
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGamerStatisticsResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Statistics/GetGamerStatistics?LocalDateTime=" + StartDate, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGamerStatisticsResponse>, callbackBinding);
	Request->ProcessRequest();
}


//-----------------Games---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::StartCareerGame(FCallbackBinding callbackBinding, FBackendStartGames request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendStartGamesResponses"))
		return;
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendStartGames>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/StartCareerGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBackendStartGamesResponses>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::StartFreeplayGame(FCallbackBinding callbackBinding, FBackendStartGamesFreeplay request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendStartGamesResponses"))
		return;
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendStartGamesFreeplay>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/StartFreeplayGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBackendStartGamesResponses>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::StartExerciseGame(FCallbackBinding callbackBinding, FBackendStartGames request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendStartGamesResponses"))
		return;
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendStartGames>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/StartExerciseGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBackendStartGamesResponses>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::StartChallengeGame(FCallbackBinding callbackBinding, FBackendStartGamesChallenge request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendStartGamesResponses"))
		return;
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendStartGamesChallenge>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/StartChallengeGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBackendStartGamesResponses>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::EndGame(FCallbackBinding callbackBinding, FBackendLevelResultToSend request, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendEndGamesResponse"))
		return;
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendLevelResultToSend>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Games/EndGame", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBackendEndGamesResponse>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::GetGameResult(FCallbackBinding callbackBinding, FString gameGuid, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendGameResult"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Games/GetGameResult?GameGuid=" + gameGuid, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBackendGameResult>, callbackBinding);
	Request->ProcessRequest();
}



//-----------------Gamers---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::GetGamerData(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendGamerData"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Gamers/GetGamerData", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendGamerData>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetGamerWeapons(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendGamerWeapons"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Gamers/GetGamerWeapons", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendGamerWeapons>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetGamerEquippedWeapons(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendGamerEquippedWeapons"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Gamers/GetGamerEquippedWeapons", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendGamerEquippedWeapons>, callbackBinding);
	Request->ProcessRequest();
}



void UBackendCommunicationComponent::EquipWeapon(FCallbackBinding callbackBinding, FBackendEquipWeapon request, const TMap<FString, FString> &headers) {
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendEquipWeapon>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Gamers/EquipWeapon", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::GetLootboxes(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGetLootBoxesResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Gamers/GetLootboxes", headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FGetLootBoxesResponse>, callbackBinding);
	Request->ProcessRequest();
}


void UBackendCommunicationComponent::OpenLootbox(FCallbackBinding callbackBinding, FlootboxId request, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FOpenLootbox"))
		return;
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FlootboxId>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Gamers/OpenLootbox", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FOpenLootbox>, callbackBinding);
	Request->ProcessRequest();
}



//-----------------SCORE---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::GetGameplaySettingsMultipliers(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FGameplaySettingsMultipliers"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Score/GetGameplaySettingsMultipliers", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FGameplaySettingsMultipliers>, callbackBinding);
	Request->ProcessRequest();
}


//-------------------------------------------------LEADERBOARDS-------------------------------------------------------------------

void UBackendCommunicationComponent::GetCareerLeaderboardByLevelType(FCallbackBinding callbackBinding, EBackendLevelType LevelType,
	int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendLeaderboard"))
		return;
	FString params = "LevelType=" + GETENUMSTRING("EBackendLevelType", LevelType);
	params += "&PageNumber=" + FString::FromInt(PageNumber);
	params += "&PageSize=" + FString::FromInt(PageSize);
	TSharedRef<IHttpRequest> Request = GetRequest("Leaderboards/GetCareerLeaderboardByLevelType?" + params, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendLeaderboard>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetCareerLeaderboardByLevel(FCallbackBinding callbackBinding, FString LevelGuid,
	int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendLeaderboard"))
		return;
	FString params = "LevelGuid=" + LevelGuid + "&PageNumber=" + FString::FromInt(PageNumber) + "&PageSize=" + FString::FromInt(PageSize);
	TSharedRef<IHttpRequest> Request = GetRequest("Leaderboards/GetCareerLeaderboardByLevel?" + params, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendLeaderboard>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetFreeplayLeaderboardByLevel(FCallbackBinding callbackBinding, FString LevelGuid,
	int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendLeaderboard"))
		return;
	FString params = "LevelGuid=" + LevelGuid + "&PageNumber=" + FString::FromInt(PageNumber) + "&PageSize=" + FString::FromInt(PageSize);
	TSharedRef<IHttpRequest> Request = GetRequest("Leaderboards/GetFreeplayLeaderboardByLevel?" + params, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendLeaderboard>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetFreeplayLeaderboardByLevelAndCountry(FCallbackBinding callbackBinding, FString LevelGuid, FString CountryCode, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendLeaderboard"))
		return;
	FString params = "LevelGuid=" + LevelGuid + "&CountryCode=" + CountryCode + "&PageNumber=" + FString::FromInt(PageNumber) + "&PageSize=" + FString::FromInt(PageSize);
	TSharedRef<IHttpRequest> Request = GetRequest("Leaderboards/GetFreeplayLeaderboardByLevelAndCountry?" + params, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendLeaderboard>, callbackBinding);
	Request->ProcessRequest();
}



void UBackendCommunicationComponent::GetChallengeLeaderboardByChallengeAndLevel(FCallbackBinding callbackBinding, FString LevelGuid,
	FString ChallengeGuid, int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendLeaderboard"))
		return;
	FString params = "LevelGuid=" + LevelGuid;
	params += "&ChallengeGuid=" + ChallengeGuid;
	params += "&PageNumber=" + FString::FromInt(PageNumber);
	params += "&PageSize=" + FString::FromInt(PageSize);
	TSharedRef<IHttpRequest> Request = GetRequest("Leaderboards/GetChallengeLeaderboardByChallengeAndLevel?" + params, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendLeaderboard>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetChallengeLeaderboardByChallenge(FCallbackBinding callbackBinding, FString ChallengeGuid,
	int32 PageNumber, int32 PageSize, const TMap<FString, FString> &headers)
{
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendLeaderboard"))
		return;
	FString params = "ChallengeGuid=" + ChallengeGuid;
	params += "&PageNumber=" + FString::FromInt(PageNumber);
	params += "&PageSize=" + FString::FromInt(PageSize);
	TSharedRef<IHttpRequest> Request = GetRequest("Leaderboards/GetChallengeLeaderboardByChallenge?" + params, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendLeaderboard>, callbackBinding);
	Request->ProcessRequest();

}



//-----------------Purchases---------------------------------------------------------------------------------//

void UBackendCommunicationComponent::GetEnergyCoins(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendEnergyCoinsResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Purchases/GetEnergyCoins", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBackendEnergyCoinsResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::GetOrderStatus(FCallbackBinding callbackBinding, FString guid, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendOrderStatusResponse"))
		return;
	TSharedRef<IHttpRequest> Request = GetRequest("Purchases/GetOrderStatus?Guid=" + guid, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived<FBackendOrderStatusResponse>, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::BuyNowWithEnergyCoins(FCallbackBinding callbackBinding, FBackendBuyEnergyCoins request, const TMap<FString, FString> &headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FBackendBuyEnergyCoinsResponse"))
		return;
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FBackendBuyEnergyCoins>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Purchases/BuyNowWithEnergyCoins", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UBackendCommunicationComponent::OnResponseReceived<FBackendBuyEnergyCoinsResponse>, callbackBinding);
	Request->ProcessRequest();
}

//-----------------OCULUS---------------------------------------------------------------------------------//






void UBackendCommunicationComponent::GetOculusAccessToken()
{

	ovrRequest RequestId = ovr_User_GetAccessToken();
	FOnlineSubsystemOculus* OSS = static_cast<FOnlineSubsystemOculus*>(IOnlineSubsystem::Get());
	OSS->AddRequestDelegate(RequestId, FOculusMessageOnCompleteDelegate::CreateLambda([this](ovrMessageHandle Message, bool bIsError)
	{
		if (bIsError) {
			UE_LOG(LogTemp, Log, TEXT("Error"));
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("Access Token OCULUS TESTAS2 : %s"), *FString(ovr_Message_GetString(Message)));
			GetOculusToken.Broadcast(ovr_Message_GetString(Message));
		}
	}
	)
	);
}





//-----------------UserSessions---------------------------------------------------------------------------------//
void UBackendCommunicationComponent::StartUserSessions(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	TSharedRef<IHttpRequest> Request = PostRequestNoJson("UserSessions/Start", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}

void UBackendCommunicationComponent::EndUserSessions(FCallbackBinding callbackBinding, const TMap<FString, FString> &headers) {
	TSharedRef<IHttpRequest> Request = PostRequestNoJson("UserSessions/End", headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UBackendCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}