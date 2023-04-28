// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common.generated.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

UENUM(BlueprintType)
enum class EBackendLevelType : uint8
{
	None,
	Boxing UMETA(DisplayName = "Boxing"),
	Swording UMETA(DisplayName = "Swording"),
	Shooting UMETA(DisplayName = "Shooting"),
	WeaponMastery UMETA(DisplayName = "WeaponMastery"),
	Exercising  UMETA(DisplayName = "Exercising "),
};


UENUM(BlueprintType)
enum class EPauseMenuButtonTypes : uint8
{
	Total UMETA(DisplayName = "Total"),
	Challenge UMETA(DisplayName = "Challenge"),
	ChallengeWithoutRestart UMETA(DisplayName = "ChallengeWithoutRestart"),
};


UENUM(BlueprintType)
enum class EUnrankedReason : uint8
{
	None,
	PauseActivated UMETA(DisplayName = "PauseActivated"),
	LevelFailed UMETA(DisplayName = "LevelFailed"),
	OfflineGame  UMETA(DisplayName = "OfflineGame "),
	SuspectedCheating  UMETA(DisplayName = "SuspectedCheating "),
};

UENUM(BlueprintType)
enum class EOrderResult : uint8
{
	None,
	Draft UMETA(DisplayName = "Draft"),
	Confirmed UMETA(DisplayName = "Confirmed"),
	Paid UMETA(DisplayName = "Paid"),
	Canceled UMETA(DisplayName = "Canceled"),
	Completed   UMETA(DisplayName = "Completed "),
};

UENUM(BlueprintType)
enum class EOrderStatus : uint8
{
	None,
	OK UMETA(DisplayName = "OK"),
	ProductPriceChanged UMETA(DisplayName = "ProductPriceChanged"),
	ProductNotAvailable UMETA(DisplayName = "ProductNotAvailable"),
	PurchaseLimitReached UMETA(DisplayName = "PurchaseLimitReached"),
	TransactionFailed  UMETA(DisplayName = "TransactionFailed"),
	InsufficientFunds  UMETA(DisplayName = "InsufficientFunds"),
	OrderCanceled   UMETA(DisplayName = "OrderCanceled"),
};


//-----------------EnemyConfig---------------------------------------------------------------------------------//

UENUM(BlueprintType)
enum class EEnemyConfigOrb : uint8
{
	None,
	Spawn UMETA(DisplayName = "Spawn"),
	Move UMETA(DisplayName = "Move"),
	TailLocation   UMETA(DisplayName = "TailLocation"),
	HitLocation   UMETA(DisplayName = "HitLocation "),
	FinalHitLocation   UMETA(DisplayName = "FinalHitLocation "),
	DestroyLocation   UMETA(DisplayName = "DestroyLocation "),
};

UENUM(BlueprintType)
enum class EEnemyConfigObstacle : uint8
{
	None,
	Spawn UMETA(DisplayName = "Spawn"),
	Move UMETA(DisplayName = "Move"),
	DisappearLocation  UMETA(DisplayName = "DisappearLocation"),
	DepthEndLocation  UMETA(DisplayName = "DepthEndLocation"),
};

UENUM(BlueprintType)
enum class EEnemyConfigShooting : uint8
{
	None,
	Spawn UMETA(DisplayName = "Spawn"),
	Move UMETA(DisplayName = "Move"),
	SingleFire  UMETA(DisplayName = "SingleFire"),
	StartFire  UMETA(DisplayName = "StartFire"),
	EndFire  UMETA(DisplayName = "EndFire"),
	KillableLocation  UMETA(DisplayName = "KillableLocation"),
	UnkillableLocation  UMETA(DisplayName = "UnkillableLocation"),
	ToggleVisibility UMETA(DisplayName = "ToggleVisibility"),

};

UENUM(BlueprintType)
enum class EBackendWeaponsType : uint8
{
	None,
	Gloves UMETA(DisplayName = "Gloves"),
	Swords UMETA(DisplayName = "Swords"),
	Guns  UMETA(DisplayName = "Guns"),
	ExerciseGloves UMETA(DisplayName = "ExerciseGloves "),
};

UENUM(BlueprintType)
enum class EGameType : uint8
{
	None,
	Career UMETA(DisplayName = "Career"),
	Challenge UMETA(DisplayName = "Weekly Challenges"),
	FreePlay   UMETA(DisplayName = "FreePlay aka Music Mode "),
	Exercises UMETA(DisplayName = "Exercises"),
};

UENUM(BlueprintType)
enum class EBackendBadge : uint8
{
	IsValid UMETA(DisplayName = "IsValid"),
	None UMETA(DisplayName = "None"),
	Bronze UMETA(DisplayName = "Bronze"),
	Silver  UMETA(DisplayName = "Silver"),
	Gold  UMETA(DisplayName = "Gold"),
};

UENUM(BlueprintType)
enum class EBackendDayOfWeek : uint8
{
	None,
	Monday  UMETA(DisplayName = "Monday "),
	Saturday    UMETA(DisplayName = "Saturday  "),
	Sunday    UMETA(DisplayName = "Sunday  "),
};

UENUM(BlueprintType)
enum class EEnvironmentType : uint8
{
	Norway UMETA(DisplayName = "Norway"),
	Greece UMETA(DisplayName = "Greece"),
	Canary  UMETA(DisplayName = "Canary"),
	Austria  UMETA(DisplayName = "Austria"),
	Desert  UMETA(DisplayName = "Desert"),
};

UENUM(BlueprintType)
enum class ESettingsGender : uint8
{
	Men UMETA(DisplayName = "Men"),
	Women UMETA(DisplayName = "Women"),
};

UENUM(BlueprintType)
enum class ECalibrationGender : uint8
{	
	None,
	Men UMETA(DisplayName = "Male"),
	Women UMETA(DisplayName = "Female"),
	Other UMETA(DisplayName = "Other "),
};


UENUM(BlueprintType)
enum class EGraphicQuality : uint8
{
	Low UMETA(DisplayName = "Low"),
	Medium UMETA(DisplayName = "Medium"),
	High UMETA(DisplayName = "High"),
};

UENUM(BlueprintType)
enum class ENextActionLevelResult : uint8
{
	Quit UMETA(DisplayName = "Quit"),
	Repeat UMETA(DisplayName = "Repeat"),
	NextLevel UMETA(DisplayName = "NextLevel"),
};

UENUM(BlueprintType)
enum class EWidgetResultType : uint8
{
	Tutorial UMETA(DisplayName = "Tutorial"),
	Exercises UMETA(DisplayName = "Exercises"),
	Challenge UMETA(DisplayName = "Challenge"),
	PlayList UMETA(DisplayName = "PlayList"),
	PlayListLast UMETA(DisplayName = "PlayListLast"),
	Training UMETA(DisplayName = "Training"),
	HotSeat UMETA(DisplayName = "HotSeat"),
	HotSeatLast UMETA(DisplayName = "HotSeatLast"),
};


UENUM(BlueprintType)
enum class EWidgetRoundType : uint8
{
	Clean UMETA(DisplayName = "Clean"),
	Challenge UMETA(DisplayName = "Challenge"),
	Exercises UMETA(DisplayName = "Exercises"),
	CurrentRound UMETA(DisplayName = "OnlyCurrentRound"),
	CurrentAndTotalRound UMETA(DisplayName = "CurrentRoundAndTotalRound"),
};


UENUM(BlueprintType)
enum class EBackendSortingCriteria : uint8
{
	Difficulty UMETA(DisplayName = "Difficulty"),
	ScoredBudgets UMETA(DisplayName = "ScoredBudgets"),
	TimeOfLevel  UMETA(DisplayName = "TimeOfLevel"),
	SongName  UMETA(DisplayName = "SongName"),
	CreatedBy  UMETA(DisplayName = "CreatedBy"),
	IsLevelSuggested  UMETA(DisplayName = "IsLevelSuggested"),
	PlaylistName  UMETA(DisplayName = "PlaylistName"),
	SongsCount  UMETA(DisplayName = "SongsCount"),
	PlaylistTimeDuration  UMETA(DisplayName = "PlaylistTimeDuration"),
	DateOfCreation  UMETA(DisplayName = "DateOfCreation"),
	DateOfLastPlayed  UMETA(DisplayName = "DateOfLastPlayed")
};


UENUM(BlueprintType)
enum class ElevelAvailability : uint8
{
	None,
	FreePlay UMETA(DisplayName = "FreePlay"),
	Challenge UMETA(DisplayName = "Challenge"),
	FreePlayAndChallenge UMETA(DisplayName = "FreePlayAndChallenge"),
};

UENUM(BlueprintType)
enum class EPlatformType: uint8
{
	None,
	Steam UMETA(DisplayName = "Steam"),
	VivePort UMETA(DisplayName = "VivePort"),
	OculusStore UMETA(DisplayName = "OculusStore"),
};


UENUM(BlueprintType)
enum class EitemType : uint8
{
	None,
	Weapon  UMETA(DisplayName = "Weapon "),
}; 

UENUM(BlueprintType)
enum class ELastChallengeContext : uint8
{
	None,
	GamerConfirmedAllChallengeResults  UMETA(DisplayName = "GamerConfirmedAllChallengeResults"),
	GamerHasUnconfirmedChallengeResult   UMETA(DisplayName = "GamerHasUnconfirmedChallengeResult"),
};


UENUM(BlueprintType)
enum class EchallengeStatus: uint8
{
	None,
	Created  UMETA(DisplayName = "Created"),
	Published   UMETA(DisplayName = "Published"),
	Ended    UMETA(DisplayName = "Ended "),
};

UENUM(BlueprintType)
enum class EAutoAimPowerType : uint8
{
	None,
	Weak  UMETA(DisplayName = "Weak"),
	Medium    UMETA(DisplayName = "Medium "),
	Strong    UMETA(DisplayName = "Strong "),
};