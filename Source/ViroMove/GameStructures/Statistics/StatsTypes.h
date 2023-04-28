// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructures/Common/Common.h"
#include "StatsTypes.generated.h"

//------------------------ STATISTIC -----------------------------------------

USTRUCT(BlueprintType)
struct FBackendStatisticPerLevel {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		EBackendLevelType levelType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int totalGameTimeInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		float totalCaloriesBurned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int totalPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int bestCombo;
};

USTRUCT(BlueprintType)
struct FBackendStatisticPerFreePlay {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int totalGameTimeInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		float totalCaloriesBurned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int numberOfBadgesGold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int numberOfBadgesSilver;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int numberOfBadgesBronze;
};

USTRUCT(BlueprintType)
struct FBackendStatisticPerChallenges {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int totalGameTimeInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		float totalCaloriesBurned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int bestPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int highestWeekPoints;
};

USTRUCT(BlueprintType)
struct FBackendStatisticPerCareer {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int totalGameTimeInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		float totalCaloriesBurned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int numberOfBadgesGold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int numberOfBadgesSilver;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int numberOfBadgesBronze;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int numberOfCompletedLevels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int numberOfAvailableLevels;
};

USTRUCT(BlueprintType)
struct FBackendStatisticMain {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int gameTimeThisWeekInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int totalGameTimeInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		float totalCaloriesBurned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int totalPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int bestCombo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int numberOfCompletedLevels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int itemsCollected;
};

USTRUCT(BlueprintType)
struct FBackendStatistic {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		FBackendStatisticMain mainStatistic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		FBackendStatisticPerFreePlay freeplayStatistic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		FBackendStatisticPerChallenges challengesStatistic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		FBackendStatisticPerCareer careerStatistic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		TArray<FBackendStatisticPerLevel> statisticsPerLevelType;
};

USTRUCT(BlueprintType)
struct FBackendStatisticResponse {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		FBackendStatistic unrankedStatistic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		FBackendStatistic rankedStatistic;
};

USTRUCT(BlueprintType)
struct FGamerStatisticsPer {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		FDateTime dateFrom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		FDateTime dateTo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int timePlayingInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		int kcalBurnt;
};


USTRUCT(BlueprintType)
struct FGamerStatisticsResponse {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		FGamerStatisticsPer dailyStats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		FGamerStatisticsPer weeklyStats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistic")
		FGamerStatisticsPer monthlyStats;
};
