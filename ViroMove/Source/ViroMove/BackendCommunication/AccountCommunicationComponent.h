// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BackendCommunication/WebCommunicationBaseComponent.h"
#include "GameStructures/Steam/SteamTypes.h"

#include "AccountCommunicationComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VIROMOVE_API UAccountCommunicationComponent : public UWebCommunicationBaseComponent
{
	GENERATED_BODY()
	UAccountCommunicationComponent();

	//-----------------Steam---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Steam")
		void IsPlatformAccountRegistered(FCallbackBinding callbackBinding, EPlatformType platformType, FString steamSesionTicket, const TMap<FString, FString>& headers);

	UFUNCTION(BlueprintCallable, Category = "Steam")
		void LoginWithPlatform(FCallbackBinding callbackBinding, FPlatformLoginDate request, const TMap<FString, FString>& headers);

	UFUNCTION(BlueprintCallable, Category = "Steam")
		void LoginWithViro(FCallbackBinding callbackBinding, FPlatformLoginDate request, const TMap<FString, FString>& headers);

	//-----------------Steam Sesion Ticket---------------------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Steam")
		FString GetSessionTicket();

	UFUNCTION(BlueprintCallable, Category = "Steam")
		FString GetSteamID(APlayerController* PlayerController);

};
