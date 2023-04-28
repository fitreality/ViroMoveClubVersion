// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructures/Common/Common.h"
#include "LeaderboardTypes.generated.h"

//-------------------------LEADERBOARDS----------------------------------

USTRUCT(BlueprintType)
struct FBackendPlayerScoreRecord
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int positionOnLeaderBoard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString playerNickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int playerScoredPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isOnline;
};



USTRUCT(BlueprintType)
struct FBackendScoreStatistics
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int playerPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float percentageOfWorsePlayers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendPlayerScoreRecord> topPlayers;
};

USTRUCT(BlueprintType)
struct FBackendLeaderboardPerLevel
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString levelGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendScoreStatistics scoreStatistics;
};

USTRUCT(BlueprintType)
struct FBackendLeaderboardPerLevelType
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBackendLevelType levelType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendScoreStatistics scoreStatistics;
};

USTRUCT(BlueprintType)
struct FBackendLeaderboardPerWeek
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int weekNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendScoreStatistics scoreStatistics;
};

USTRUCT(BlueprintType)
struct FBackendLeaderboardPerWeekType
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FBackendLeaderboardPerWeek weeklyLeaderboard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBackendLevelType levelType;
};

USTRUCT(BlueprintType)
struct FBackendGamerPosition {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float points;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int playerBetterThanPercentOfPlayers;
};

USTRUCT(BlueprintType)
struct FBackendLeaderboardEntry {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ranking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString gamerGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString gamerNickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float points;
};

USTRUCT(BlueprintType)
struct FBackendLeaderboard {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float generalPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int totalCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBackendLeaderboardEntry> leaderboard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool hasGamerEverPlayedRanked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBackendGamerPosition gamerRankedPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool hasGamerEverPlayedUnranked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float gamerUnrankedPoints;
};