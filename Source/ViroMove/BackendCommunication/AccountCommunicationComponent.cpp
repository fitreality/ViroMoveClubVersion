// Fill out your copyright notice in the Description page of Project Settings.


#include "AccountCommunicationComponent.h"
#include "Online.h"
#include "GameStructures/Gameplay/GameplayTypes.h"
//#include "ThirdParty/Steamworks/Steamv142/sdk/public/steam/steam_gameserver.h"
#include <Runtime/Engine/Classes/GameFramework/PlayerController.h>
#include "OnlineSubsystem.h"

UAccountCommunicationComponent::UAccountCommunicationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


FString  UAccountCommunicationComponent::GetSessionTicket() {
	IOnlineSubsystem* OnlineInterface;
	OnlineInterface = IOnlineSubsystem::Get();
	if (!OnlineInterface) return "Not valid";
	return OnlineInterface->GetIdentityInterface()->GetAuthToken(0);

}


FString UAccountCommunicationComponent::GetSteamID(APlayerController* PlayerController) {
	FString ID = "";
	int PUID = 0;

	if (!PlayerController) return "Error";
	if (!PlayerController->PlayerState) return "error";

	//if (SteamUser() == nullptr)
		return "None";

	//CSteamID uid = SteamUser()->GetSteamID();
	//uint64 pid = uid.ConvertToUint64();

	//ID = FString::FromInt(pid);
	return ID;
}

//-----------------Platform---------------------------------------------------------------------------------//

void UAccountCommunicationComponent::IsPlatformAccountRegistered(FCallbackBinding callbackBinding, EPlatformType platformType, FString steamSesionTicket, const TMap<FString, FString>& headers) {
	if (!CheckIfCallbackIsCorrect(callbackBinding, "FPlatformIsRegisteredResponse"))
		return;
	FString SEnum;
	switch (platformType) {
	case EPlatformType::Steam: SEnum = "Steam";
		break;
	case EPlatformType::VivePort: SEnum = "VivePort";
		break;
	case EPlatformType::OculusStore: SEnum = "OculusStore";
		break;
	}
	TSharedRef<IHttpRequest> Request = GetRequest("Platform/IsPlatformAccountRegistered?Platform=" + SEnum + "&SessionTicket=" + steamSesionTicket, headers);
	Request->OnProcessRequestComplete().BindUObject(this,
		&UAccountCommunicationComponent::OnResponseReceived<FPlatformIsRegisteredResponse>, callbackBinding);
	Request->ProcessRequest();
}


void UAccountCommunicationComponent::LoginWithPlatform(FCallbackBinding callbackBinding, FPlatformLoginDate request, const TMap<FString, FString>& headers) {
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FPlatformLoginDate>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Platform/LoginWithPlatform", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UAccountCommunicationComponent::OnResponseReceived<FErrorMessages>, callbackBinding);
	Request->ProcessRequest();
}

void UAccountCommunicationComponent::LoginWithViro(FCallbackBinding callbackBinding, FPlatformLoginDate request, const TMap<FString, FString>& headers) {
	FString ContentJsonString;
	this->template GetJsonStringFromStruct<FPlatformLoginDate>(request, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("Platform/LoginWithViro", ContentJsonString, headers);
	Request->OnProcessRequestComplete().BindUObject(this, &UAccountCommunicationComponent::OnResponseReceived_void, callbackBinding);
	Request->ProcessRequest();
}
