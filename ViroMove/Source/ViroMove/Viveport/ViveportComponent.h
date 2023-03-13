// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ViveportApi.h" 
#include "ViveportUser.h"
#include "ViveportToken.h"
#include <functional>
#include "ViveportComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnViveportInitialized);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedSessionToken, const FString&, sessionToken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTokenFailure, int, errorCode);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIROMOVE_API UViveportComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UViveportComponent();

	UFUNCTION(BlueprintCallable)
	void GetUserProfileData(FString& userId, FString& userName, FString& userAvatarUrl);

	UPROPERTY(BlueprintAssignable, Category = "Viveport")
	FOnViveportInitialized onViveportInitialized;
	UPROPERTY(BlueprintAssignable, Category = "Viveport")
	FOnReceivedSessionToken onReceivedSessionToken;
	UPROPERTY(BlueprintAssignable, Category = "Viveport")
	FOnTokenFailure onTokenFailure;

	UFUNCTION(BlueprintCallable, Category = "Viveport")
	void InitVivePort();

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	class ViveportApiStatusCallback : public ViveportApiStatus
	{
	private:
		std::function<void(void)> onSuccessCallback;
		std::function<void(int error_code)> onFailure;
	public:
		void SetOnSuccessCallback(std::function<void(void)> callback, std::function<void(int error_code)> failureCallback);
		void OnSuccess() override;
		void OnFailure(int error_code) override;
	};
	class MyLicenseChecker : public UViveportApi::LicenseChecker
	{
	private:
		std::function<void(void)> onSuccessCallback;
	public:
		void SetOnSuccessCallback(std::function<void(void)> callback);
		void OnSuccess(long long issue_time, long long expiration_time, int latest_version, bool update_required) override;
		void OnFailure(int errorCode, const FString& errorMessage) override;
	};
	class MyGetSessionTokenCallback : public ViveportApiStatus2
	{
	private:
		std::function<void(const FString& token)> onSuccessCallback;
	public:
		void SetOnSuccessCallback(std::function<void(const FString& token)> callback);
		void OnSuccess(const FString& token) override;
		void OnFailure(int errorCode, const FString& errorMessage) override;
	};

	FString viveportId = "c4b94764-d3da-48df-8497-517b8fbef073";
	FString viveportToken = "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDAmF7ofrxAeAhZVROE1lAi//89HyyP8b3qZOaqCHek15evArewgz1jOzhPxyHcsnn4kAP6PSPTjqDalT55b2Lvf/pVEmV+oD2BU5svvBE20voGOE44NdKUi50n+f8ptuGWw0cbprgI1hNuCOUobMoLK8oET8PQmGjZlUyUQOFOiQIDAQAB";
	
	ViveportApiStatusCallback initCallback;
	ViveportApiStatusCallback shutdownCallback;
	ViveportApiStatusCallback isTokenReadyCallback;
	MyLicenseChecker myLicenseChecker;	
	MyGetSessionTokenCallback getSessionTokenCallback;

	bool bIsViveportInitialized;
	void BeginInitialization();

	void OnViveportHighLevelInitialized();
	void OnReceivedToken(const FString& token);
};
