//// Fill out your copyright notice in the Description page of Project Settings.
//
//#include "SpotifyCommunicationComponent.h"
//
//USpotifyCommunicationComponent::USpotifyCommunicationComponent()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = false;
//	PrimaryComponentTick.bStartWithTickEnabled = false;
//
//	testAccountGuid = "95306D7F-4769-45A9-982A-81CB3BE1D355";
//	// ...
//}
//
//void USpotifyCommunicationComponent::GetSpotifyEndpointsConfiguration(FCallbackBinding callback)
//{
//	FCallbackBinding callbackTmp;
//	callbackTmp.receiver = this;
//	callbackTmp.callbackName = "OnSpotifyClienIdReceived";
//	FString ContentJsonString;
//	UE_LOG(LogTemp, Warning, TEXT("USpotifyCommunicationComponent::GetSpotifyEndpointsConfiguration"));
//	TSharedRef<IHttpRequest> Request = GetRequest("Spotify/GetSpotifyEndpointsConfiguration");
//	Request->OnProcessRequestComplete().BindUObject(this, &USpotifyCommunicationComponent::OnResponseReceived<FSpotifyEndpointsConfigurationResponse>, callbackTmp);
//	Request->ProcessRequest();
//}
//
//void USpotifyCommunicationComponent::OnSpotifyClienIdReceived(FSpotifyEndpointsConfigurationResponse response)
//{
//	backendResponse = response;
//	const FString spotifyUrl = "https://accounts.spotify.com/authorize?response_type=code&redirect_uri={0}&client_id={1}&scope={2}";
//	FString scopes = FGenericPlatformHttp::UrlEncode(response.authorize.scope);
//	FString redirectUrl = response.authorize.redirectUri;
//	FString clientId = response.authorize.clientId;
//	TArray<FStringFormatArg> args;
//	args.Add(redirectUrl);
//	args.Add(clientId);
//	args.Add(scopes);
//	FString url = FString::Format(*spotifyUrl, args);
//	OnReadyToLogin.Broadcast(url);
//}
//
//void USpotifyCommunicationComponent::GetAccessToken(FString code)
//{
//	UE_LOG(LogTemp, Warning, TEXT("USpotifyCommunicationComponent::GetAccessToken"));
//	FCallbackBinding callbackTmp;
//	callbackTmp.receiver = this;
//	callbackTmp.callbackName = "OnAccessTokenReceived";
//	auto Request = GetCleanRequest();
//	Request->OnProcessRequestComplete().BindUObject(this, &USpotifyCommunicationComponent::OnResponseReceived<FSpotifyEndpointResponse>,callbackTmp);
//	Request->SetURL(backendResponse.accessToken.endpoint);
//	Request->SetVerb(backendResponse.accessToken.method);
//	Request->SetHeader("Content-Type", TEXT("application/x-www-form-urlencoded"));
//	Request->SetHeader("Authorization", backendResponse.accessToken.authHeader);
//	const FString Content = "grant_type={0}&redirect_uri={1}&code={2}";
//	FString left, right;
//	backendResponse.accessToken.authHeader.Split("Basic ", &left, &right);
//	TArray<FStringFormatArg> args;
//	args.Add(backendResponse.accessToken.grantType);
//	args.Add(backendResponse.accessToken.redirectUri);
//	args.Add(code);
//	FString body = FString::Format(*Content, args);
//	Request->SetContentAsString(body);
//	Request->ProcessRequest();
//}
//
//void USpotifyCommunicationComponent::PausePlayback(FString accountGuid)
//{
//	accountGuid = testAccountGuid;
//	FSpotifyBaseRequest param;
//	param.accountGuid = accountGuid;
//	FString jsonString;
//	GetJsonStringFromStruct<FSpotifyBaseRequest>(param, jsonString);
//	auto request = PostRequest("Spotify/PausePlayback", jsonString);
//	request->OnProcessRequestComplete().BindUObject(this, &USpotifyCommunicationComponent::OnResponseReceived_void);
//	request->ProcessRequest();
//}
//
//void USpotifyCommunicationComponent::ResumePlayback(FString accountGuid)
//{
//	accountGuid = testAccountGuid;
//	FSpotifyBaseRequest param;
//	param.accountGuid = accountGuid;
//	FString jsonString;
//	GetJsonStringFromStruct<FSpotifyBaseRequest>(param, jsonString);
//	auto request = PostRequest("Spotify/ResumePlayback", jsonString);
//	request->OnProcessRequestComplete().BindUObject(this, &USpotifyCommunicationComponent::OnResponseReceived_void);
//	request->ProcessRequest();
//}
//
//void USpotifyCommunicationComponent::NextTrackPlayback(FString accountGuid)
//{
//	accountGuid = testAccountGuid;
//	FSpotifyBaseRequest param;
//	param.accountGuid = accountGuid;
//	FString jsonString;
//	GetJsonStringFromStruct<FSpotifyBaseRequest>(param, jsonString);
//	auto request = PostRequest("Spotify/NextTrackPlayback", jsonString);
//	request->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnResponseReceived_void);
//	request->ProcessRequest();
//}
//
//void USpotifyCommunicationComponent::PreviousTrackPlayback(FString accountGuid)
//{
//	accountGuid = testAccountGuid;
//	FSpotifyBaseRequest param;
//	param.accountGuid = accountGuid;
//	FString jsonString;
//	GetJsonStringFromStruct<FSpotifyBaseRequest>(param, jsonString);
//	auto request = PostRequest("Spotify/PreviousTrackPlayback", jsonString);
//	request->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnResponseReceived_void);
//	request->ProcessRequest();
//}
//
//void USpotifyCommunicationComponent::SetDevice(FSetDeviceRequest request)
//{
//}
//
//void USpotifyCommunicationComponent::PlayTracksRequest(FPlayTracksRequest request)
//{
//}
//
//void USpotifyCommunicationComponent::GetDevices(FString stationGuid)
//{
//}
//
//void USpotifyCommunicationComponent::OnAccessTokenReceived(FSpotifyEndpointResponse response)
//{
//	FAddUserAuthorizationsRequest request;
//	request.accessToken = response.access_token;
//	request.tokenExpirationTimeInSeconds = response.expires_in;
//	request.refreshToken = response.refresh_token;
//	FDateTime timeNow = FDateTime::UtcNow();
//	request.tokenGrantUtcDate = timeNow.ToIso8601();
//	request.accountGuid = testAccountGuid;
//
//	FString jsonContent;
//	GetJsonStringFromStruct<FAddUserAuthorizationsRequest>(request, jsonContent);
//
//	UE_LOG(LogTemp, Warning, TEXT("USpotifyCommunicationComponent::OnAccessTokenReceived %s"), *jsonContent);
//
//	FCallbackBinding binding;
//	binding.receiver = this;
//	binding.callbackName = "OnAddUserAuthorization";
//
//	auto Request = PostRequest("Spotify/AddUserAuthorization", jsonContent);
//	Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::OnResponseReceived_void, binding);
//	Request->ProcessRequest();
//}
//
//void USpotifyCommunicationComponent::OnAddUserAuthorization()
//{
//	OnAuthorizationSucceeded.Broadcast();
//}
//
