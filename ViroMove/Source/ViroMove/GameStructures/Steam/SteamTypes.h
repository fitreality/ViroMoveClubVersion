#pragma once

#include "CoreMinimal.h"
#include "GameStructures/Common/Common.h"
#include "SteamTypes.generated.h"

//--------------------------Steam----------------------------------//

USTRUCT(BlueprintType)
struct FPlatformLoginDate
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EPlatformType platform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString sessionTicket;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString nickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString countryCode;
};

USTRUCT(BlueprintType)
struct FPlatformIsRegisteredResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAccountPlatformConnectedWithViroAccount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAccountPlatformRegistered;

};
