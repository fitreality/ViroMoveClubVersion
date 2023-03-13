// Fill out your copyright notice in the Description page of Project Settings.


#include "ViveportComponent.h"
#include "Engine.h"


// Sets default values for this component's properties
UViveportComponent::UViveportComponent() : bIsViveportInitialized(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UViveportComponent::BeginInitialization()
{

}

void UViveportComponent::InitVivePort()
{
	FString fstring = UViveportApi::Version();
	UE_LOG(LogTemp, Warning, TEXT("UViveportComponent::MyLicenseChecker::BeginPlay version= %s"), *fstring);
	initCallback.SetOnSuccessCallback(
		[&]() {OnViveportHighLevelInitialized(); },
		[&](int error_code) {onTokenFailure.Broadcast(error_code);}
	);
	UViveportApi::Init(&initCallback, viveportId);
}

void UViveportComponent::OnViveportHighLevelInitialized()
{
	bIsViveportInitialized = true;
	onViveportInitialized.Broadcast();
	isTokenReadyCallback.SetOnSuccessCallback([&]() 
		{
		getSessionTokenCallback.SetOnSuccessCallback([&](const FString& token) { OnReceivedToken(token); });
			UViveportToken::GetSessionToken(&getSessionTokenCallback);
	}, [&](int error_code) {onTokenFailure.Broadcast(error_code);}
	);
	UViveportToken::IsReady(&isTokenReadyCallback);
}

void UViveportComponent::GetUserProfileData(FString& userId, FString& userName, FString& userAvatarUrl)
{
	if (!bIsViveportInitialized)
	{
		userId = "VIVEPORT NOT YET INITIALIZED";
		userName = "VIVEPORT NOT YET INITIALIZED";
		userAvatarUrl = "VIVEPORT NOT YET INITIALIZED";
		return;
	}
	userId = UViveportUser::GetUserID();
	userName = UViveportUser::GetUserName();
	userAvatarUrl = UViveportUser::GetUserAvatarUrl();
}

void UViveportComponent::OnReceivedToken(const FString& token)
{
	UE_LOG(LogTemp, Warning, TEXT("UViveportComponent::OnReceivedToken %s"), *token);
	onReceivedSessionToken.Broadcast(token);
}


// Called when the game starts
void UViveportComponent::BeginPlay()
{
	Super::BeginPlay();
	BeginInitialization();
	// ...

}

void UViveportComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UViveportApi::Shutdown(&shutdownCallback);
}


// Called every frame
void UViveportComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UViveportComponent::ViveportApiStatusCallback::SetOnSuccessCallback(std::function<void(void)> callback, std::function<void(int error_code)> failureCallback)
{
	onSuccessCallback = callback;
	onFailure = failureCallback;
}

void UViveportComponent::ViveportApiStatusCallback::OnSuccess()
{
	UE_LOG(LogTemp, Warning, TEXT("UViveportComponent:ViveportApiStatusCallback OnSuccess"));
	if(onSuccessCallback) onSuccessCallback();
}

void UViveportComponent::ViveportApiStatusCallback::OnFailure(int error_code)
{
	UE_LOG(LogTemp, Warning, TEXT("UViveportComponent:ViveportApiStatusCallback OnFailure"));
	if(onFailure) onFailure(error_code);
}
void UViveportComponent::MyLicenseChecker::SetOnSuccessCallback(std::function<void(void)> callback)
{
	onSuccessCallback = callback;
}

void UViveportComponent::MyLicenseChecker::OnSuccess(long long issue_time, long long expiration_time, int latest_version, bool update_required)
{
	UE_LOG(LogTemp, Warning, TEXT("UViveportComponent:MyLicenseChecker OnSuccess"));
	if (onSuccessCallback) onSuccessCallback();
}

void UViveportComponent::MyLicenseChecker::OnFailure(int errorCode, const FString& errorMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("UViveportComponent:MyLicenseChecker OnFailure"));
}

void UViveportComponent::MyGetSessionTokenCallback::SetOnSuccessCallback(std::function<void(const FString& token)> callback)
{
	onSuccessCallback = callback;
}

void UViveportComponent::MyGetSessionTokenCallback::OnSuccess(const FString& token)
{
	UE_LOG(LogTemp, Warning, TEXT("UViveportComponent:MyGetSessionTokenCallback OnSuccess"));
	if (onSuccessCallback) onSuccessCallback(token);
}

void UViveportComponent::MyGetSessionTokenCallback::OnFailure(int errorCode, const FString& errorMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("UViveportComponent:MyGetSessionTokenCallback OnFailure"));
}
