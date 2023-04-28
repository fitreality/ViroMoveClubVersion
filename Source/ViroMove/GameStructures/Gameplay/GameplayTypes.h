// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructures/Common/Common.h"
#include "GameStructures/Leaderboards/LeaderboardTypes.h"
#include "OpenVRExpansionPlugin/Public/OpenVRExpansionFunctionLibrary.h"
#include "OpenVRExpansionFunctionLibrary.h"
#include "GameplayTypes.generated.h"


USTRUCT(BlueprintType)
struct FCountriesElem
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString countryName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString countryCode;
};

USTRUCT(BlueprintType)
struct FCountriesList
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString suggestedCountryCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FCountriesElem> countries;
};

//--------------------------ENEYM----------------------------------//

USTRUCT(BlueprintType)
struct FErrorMessages
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString messages;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int errorCode;
};


//--------------------------ENEYM----------------------------------//

USTRUCT(BlueprintType)
struct FEnemyConfig
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString actionType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector> actionLocations;
};

USTRUCT(BlueprintType)
struct FBackendEnemySet
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnemyScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FEnemyConfig> EnemyConfig;
};

USTRUCT(BlueprintType)
struct FBackendTempExercises
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* ExercisesClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int repetitions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool OffsetRghtLeft;
};


//--------------------------SONG----------------------------------//

USTRUCT(BlueprintType)
struct FBackendSongDataStruct
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString author;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int bpm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString spotifyLink;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString spotifyCoverLink;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localLink;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localCoverLink;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float songStartTimeInSec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float previewSongStartTimeInSec;
};

USTRUCT(BlueprintType)
struct FBackendPlaylist
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString playlistGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString author;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int durationInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString lastPlayedDateInUtc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString createdDateInUtc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> levelGuids;
	//TODO FIX FOR MAPS!!!!!
	bool operator== (const FBackendPlaylist& Other)
	{
		return playlistGuid == Other.playlistGuid;
	}

	friend uint32 GetTypeHash(const FBackendPlaylist& Other)
	{
		return GetTypeHash(Other.playlistGuid);
	}
};


USTRUCT(BlueprintType)
struct FBackendPlayListResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendPlaylist playlist;
};

USTRUCT(BlueprintType)
struct FBackendPlayListsResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendPlaylist> playlists;
};


USTRUCT(BlueprintType)
struct FBackendPlayListCreate
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString playlistGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localCreateDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> levelGuids;
};




USTRUCT(BlueprintType)
struct FBackendPlayListGuid
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString playlistGuid;

};



USTRUCT(BlueprintType)
struct FBackendPlayListUpdate
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString playlistGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> levelGuids;
};
//--------------------------GAMEPLAYSETTINGS----------------------------------//

USTRUCT(BlueprintType)
struct FGameplaySettings {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplaySettings")
		bool AutoWeaponSwitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplaySettings")
		bool Immortality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplaySettings")
		EAutoAimPowerType AutoAimPower;
};



//--------------------------USERS----------------------------------//

USTRUCT(BlueprintType)
struct FBackendAthletedData
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float weightInKilograms;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int heightInCentimeters;
};


USTRUCT(BlueprintType)
struct FBackendMeasurementDataRequest
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendAthletedData athleteData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ECalibrationGender gender;
};


USTRUCT(BlueprintType)
struct FBackendCalibrationDetailed
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int HeightPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int HeightCentralPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int DistanceToArmFromCenter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lenghtHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HorizontalRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WeightPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LenghtHandPartHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LenghtHandPartArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ECalibrationGender PlayerGender;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CountImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime DataTimeUpdate;
};

USTRUCT(BlueprintType)
struct FBackendCalibration
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString nicknameLocalPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendCalibrationDetailed Calibraction;
};

USTRUCT(BlueprintType)
struct FBackendProfileSettings
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentProfileCalibraction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBackendDayOfWeek firstDayOfWeek;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MusicVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LectorVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EffectsVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float  GameplayLectorVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ESettingsGender LectorGander;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGraphicQuality graphicQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGraphicQuality effectQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float resolutionScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SafetyWall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SafetyOutsideZone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SafetyVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool activePauseButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool fearofheights;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplaySettings GameplaySettings;
	
};

USTRUCT(BlueprintType)
struct FBackendCreditItem
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString role;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> authors;
};

USTRUCT(BlueprintType)
struct FBackendCredits
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendCreditItem> creditItems;
};

//--------------------------LEVEL----------------------------------//

USTRUCT(BlueprintType)
struct FBackendLevelStructDetailed
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LevelGUID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendEnemySet> enemySet;
};

USTRUCT(BlueprintType)
struct FBackendlevelAvailability
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool availableInFreeplay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool availableInCareer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool availableInChallenge;
};


USTRUCT(BlueprintType)
struct FBackendLevelStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString createdDateUtc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelAuthor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBackendLevelType levelType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendlevelAvailability levelAvailability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray< EBackendWeaponsType> availableWeapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 difficultyLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString environment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int levelLengthInSec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int32> pointsForBadge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isRecommended;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float levelSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendSongDataStruct songData;

	bool operator== (const FBackendLevelStruct& Other)
	{
		bool areEqual = levelGuid == Other.levelGuid && levelType == Other.levelType && difficultyLevel == Other.difficultyLevel &&
			environment == Other.environment && levelAuthor == Other.levelAuthor && levelLengthInSec == Other.levelLengthInSec &&
			maxPoints == Other.maxPoints && isRecommended == Other.isRecommended;
		return areEqual;
	}

	friend uint32 GetTypeHash(const FBackendLevelStruct& Other)
	{
		return GetTypeHash(Other.levelGuid) ^ GetTypeHash(Other.levelType) ^ GetTypeHash(Other.difficultyLevel) ^ GetTypeHash(Other.environment) ^ GetTypeHash(Other.levelLengthInSec) ^
			GetTypeHash(Other.maxPoints) ^ GetTypeHash(Other.levelAuthor) ^ GetTypeHash(Other.isRecommended);
	}
};

USTRUCT(BlueprintType)
struct FBackendLevelRequest
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendLevelStruct levelStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendLevelStructDetailed levelStructDetailed;
};

USTRUCT(BlueprintType)
struct FBackendLevelsRequest
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int totalCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendLevelRequest> levels;
};

USTRUCT(BlueprintType)
struct FBackendLevelResponseChallenges
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString guid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBackendLevelType type;
};

USTRUCT(BlueprintType)
struct FChallengeRewardsGrand {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int challengeParticipantPlace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int energyCoinsAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lootboxesCount;
};

USTRUCT(BlueprintType)
struct FChallengeRewardsConsolation {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int challengeParticipantsPercentRangeTo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int energyCoinsAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lootboxesCount;
};

USTRUCT(BlueprintType)
struct FChallengeResponsePast
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString guid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime utcStartDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime utcEndDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplaySettings GameplaySettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendLevelResponseChallenges> levels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int gamesLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EchallengeStatus challengeStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int challengeNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> challengeWinnersNicknames;
};

USTRUCT(BlueprintType)
struct FChallengeResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString guid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString utcStartDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString utcEndDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplaySettings GameplaySettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendLevelResponseChallenges> levels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int challengeNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FChallengeRewardsGrand> challengeRewardsGrand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FChallengeRewardsConsolation> challengeRewardsConsolation;
};


USTRUCT(BlueprintType)
struct FChallengePastResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString guid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString utcStartDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString utcEndDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendLevelResponseChallenges> levels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int gamesLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int usedGamesLimit;
};



USTRUCT(BlueprintType)
struct FCurrentChallengeResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool currentChallengeExists;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FChallengeResponse currentChallenge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime nextChallengeStartDateUtc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool nextChallengeExists;

};

USTRUCT(BlueprintType)
struct FPastChallengeResponse
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FChallengeResponsePast> challenges;
};

USTRUCT(BlueprintType)
struct FConfirmChallengeResult
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString challengeGuid;
};

USTRUCT(BlueprintType)
struct FChallengeLimitsResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int gamesLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int usedGamesLimit;
};

USTRUCT(BlueprintType)
struct FOpenLootboxResponse{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString itemGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EitemType itemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int energyCoinsGained;
};


USTRUCT(BlueprintType)
struct FConfirmChallengeResults {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lootboxesWonInChallengeCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int energyCoinsWonInChallenge;
};

USTRUCT(BlueprintType)
struct FUnclaimedChallengeReward {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int gamerChallengeRewardId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int energyCoinsAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lootboxesAmount;
};

USTRUCT(BlueprintType)
struct FLastChallengeContext {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString challengeGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int challengeNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FUnclaimedChallengeReward> challengeRewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendGamerPosition gamerRankedPosition;
};

USTRUCT(BlueprintType)
struct FGamerLastChallengeContext {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ELastChallengeContext status;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLastChallengeContext lastChallengeContext;
};





USTRUCT(BlueprintType)
struct FSaveChallenge
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString utcStartDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString utcEndDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> levelGuids;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int gamesLimit;
};


USTRUCT(BlueprintType)
struct FSaveChallengeResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString challengeGuid;
};

USTRUCT(BlueprintType)
struct FBackendFavouriteLevel
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelGuid;
};


	//Response
USTRUCT(BlueprintType)
struct FBackendLevelResponses
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelGuid;
};

USTRUCT(BlueprintType)
struct FBackendGetFavouriteLevel
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendFavouriteLevel> results;
};


USTRUCT(BlueprintType)
struct FBackendGetLevelsByTimestamp
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isDeleted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendLevelStruct levelStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendLevelStructDetailed levelStructDetailed;
};

USTRUCT(BlueprintType)
struct FBackendGetLevelsByTimestampResponse
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int totalCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxTimestamp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendGetLevelsByTimestamp> levels;
};




//--------------------------RESULTS----------------------------------//

USTRUCT(BlueprintType)
struct FBackendLevelResult
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Points;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBackendBadge BadgeEarned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int GameTimeInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CaloriesBurned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int BestCombo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MovePoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MovePointsPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isUnranked;
};

USTRUCT(BlueprintType)
struct FBackendLevelResultEndGame
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int targetsScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBackendBadge BadgeEarned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MovePoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int GameTimeInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CaloriesBurned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MovePointsPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int BestCombo;
};

USTRUCT(BlueprintType)
struct FBackendLevelResultToSend
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gameGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localEndDateTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> unrankedReasons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendLevelResultEndGame levelResult;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplaySettings GameplaySettings;

};

USTRUCT(BlueprintType)
struct FBackendLevelResultToSendOffline
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGameType GameType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString playlistGUID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gameGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString utcStartDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString utcEndDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendLevelResultEndGame levelResult;
};


USTRUCT(BlueprintType)
struct FBackendBestResults
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendLevelResult>  results;
};


USTRUCT(BlueprintType)
struct FBackendHotSeatResults
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendLevelResult> Results;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int TotalPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendCalibration Player;
};


USTRUCT(BlueprintType)
struct FBackendGameResult
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int playerPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int playerBetterThanPercentOfPlayers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PointsEarned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int EnergyCoinsEarned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isUnranked;
};






//--------------------------USER2------------------------------//
USTRUCT(BlueprintType)
struct FHandTransform {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HandTransform")
		FTransform RightHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HandTransform")
		FTransform LeftHand;
};

USTRUCT(BlueprintType)
struct FWeaponTransform {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HandTransform")
		TMap<EBackendWeaponsType, FHandTransform> WeaponRelativeTransform;
};

USTRUCT(BlueprintType)
struct FBackendProfile
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString nickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int  energyCoins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendCalibration> calibrationProfiles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendLevelResult> playerResultPerLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendProfileSettings profileSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> favouriteSong;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> createdSong;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> lootboxes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<EBPOpenVRHMDDeviceType, FWeaponTransform> ControllerTypeToWeaponTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString country;

};

//--------------------------Activities----------------------------------//

USTRUCT(BlueprintType)
struct FBackendStartGames
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localStartDateTime;
};

USTRUCT(BlueprintType)
struct FBackendStartGamesFreeplay
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString playlistGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localStartDateTime;
};


USTRUCT(BlueprintType)
struct FBackendStartGamesChallenge
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString challengeGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localStartDateTime;
};

USTRUCT(BlueprintType)
struct FBackendEndGame
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gameGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString localEndDateTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendLevelResult levelResult;
};

	//Response
USTRUCT(BlueprintType)
struct FBackendStartGamesResponses
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gameGuid;
};


USTRUCT(BlueprintType)
struct FBackendEndGamesResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString activityGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime startDateTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime endDateTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isUnranked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MovePoints;
};


//--------------------------SAVE----------------------------------//

USTRUCT(BlueprintType)
struct FSaveLocalGamesSlot
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SlotName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime createdDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendLevelRequest LevelRequest;
};


USTRUCT(BlueprintType)
struct FSaveLocalGames
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Guid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FSaveLocalGamesSlot> SlotGames;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendLevelRequest> lastTenAutosaveSong;
};

//--------------------------IHRSA----------------------------------//

USTRUCT(BlueprintType)
struct FActiveUser {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString userGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString nickname;
};

USTRUCT(BlueprintType)
struct FFitnessGameSummary {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString stationGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString userGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString nickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		int score;
};

USTRUCT(BlueprintType)
struct FleaderboardPosition {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		int leaderboardPosition;
};

USTRUCT(BlueprintType)
struct FRemoveUser {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IHRSA")
		FString stationGuid;
};

//------------------------TRAINING MODE LEVELS -----------------------------------------

USTRUCT(BlueprintType)
struct FCareerModeLevels {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		int order;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		FString levelGuid;
};

USTRUCT(BlueprintType)
struct FCareerLevelsResponse {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		EBackendLevelType levelType;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
		TArray<FCareerModeLevels> levels;
};


//------------------------WEEKLY CHALLENGES-----------------------------------------

USTRUCT(BlueprintType)
struct FBackendGamerData {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamerData")
		FString nickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString countryCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamerData")
		int energyCoinsAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamerData")
		TArray<FString> favouriteLevels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamerData")
		TArray<FString> createdLevels;

};


//------------------------LootBox-----------------------------------------

USTRUCT(BlueprintType)
struct FlootboxId {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamerData")
		int lootboxId;
};

USTRUCT(BlueprintType)
struct FGetLootBoxesResponse {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamerData")
		TArray<FlootboxId> lootboxes;
};

USTRUCT(BlueprintType)
struct FOpenLootbox {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamerData")
		FString itemGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamerData")
		EitemType itemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamerData")
		int energyCoinsGained;
};

//------------------------GameplaySettings-----------------------------------------



USTRUCT(BlueprintType)
struct FGameplaySettingsMultipliers {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplaySettings")
		float AutoWeaponSwitchOn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplaySettings")
		float AutoWeaponSwitchOff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplaySettings")
		float ImmortalityOn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplaySettings")
		float ImmortalityOff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplaySettings")
		float AutoAimPowerWeak;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplaySettings")
		float AutoAimPowerMedium;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplaySettings")
		float AutoAimPowerStrong;
};


