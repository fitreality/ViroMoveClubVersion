// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructures/Gameplay/GameplayTypes.h"
#include "MiniGames/Weapon.h"
#include "MiniGames/CaptureObjectContainer.h"
#include <Engine/Texture2D.h>
#include "Engine/DataTable.h"
#include "GearTypes.generated.h"




UENUM(BlueprintType)
enum class EBackendWeaponStatus : uint8
{
	None,
	Owned UMETA(DisplayName = "Owned"),
	availableToBuy UMETA(DisplayName = "availableToBuy"),
	availableWithAchievement UMETA(DisplayName = "availableWithAchievement"),
	availableAfterChallenge UMETA(DisplayName = "availableAfterChallenge")
};

USTRUCT(BlueprintType)
struct FBackendWeaponItem : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString guid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBackendWeaponsType weaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBackendWeaponStatus weaponStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<AWeapon> weaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* weaponMiniature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<ACaptureObjectContainer> captureWeaponStudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString additionalMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString productGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString categoryName;


	FBackendWeaponItem()
	{
		guid = FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens);
	}
};


USTRUCT(BlueprintType)
struct FBackendGear
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendWeaponItem> avaiableWeapons;
};


USTRUCT(BlueprintType)
struct FBackendGamerWeaponsItemOwned
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isEquipped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString weaponGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBackendWeaponsType weaponType;
};

USTRUCT(BlueprintType)
struct FBackendGamerWeaponsItemBuy
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int priceInEnergyCoins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString productGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString categoryName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString weaponGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBackendWeaponsType weaponType;
};

USTRUCT(BlueprintType)
struct FBackendGamerWeaponsItemImmpossibleToBuy
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString weaponGuid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBackendWeaponsType weaponType;
};


USTRUCT(BlueprintType)
struct FBackendGamerEquippedWeaponsItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBackendWeaponsType weaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString weaponGuid;
};

USTRUCT(BlueprintType)
struct FBackendGamerEquippedWeapons
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendGamerEquippedWeaponsItem> gamerEquippedWeapons;
};


USTRUCT(BlueprintType)
struct FBackendGamerWeapons
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendGamerWeaponsItemOwned> ownedWeapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendGamerWeaponsItemBuy> weaponsToBuy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBackendGamerWeaponsItemImmpossibleToBuy> weaponsImpossibleToBuy;
};

USTRUCT(BlueprintType)
struct FBackendEquipWeapon
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString weaponGuid;
};


USTRUCT(BlueprintType)
struct FBackendBuyEnergyCoins
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString productId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString categoryName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float price;
};

USTRUCT(BlueprintType)
struct FBackendBuyEnergyCoinsResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EOrderStatus orderResultStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString orderGuid;
};


USTRUCT(BlueprintType)
struct FBackendOrderStatusResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EOrderResult orderStatus;
};


USTRUCT(BlueprintType)
struct FBackendEnergyCoinsResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int energyCoins;
};
