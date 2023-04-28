#pragma once

#include "CoreMinimal.h"
#include "SpotifyTypes.generated.h"



//--------------------------SPOTIFY----------------------------------//

USTRUCT(BlueprintType)
struct FAuthorizeResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString clientId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString endpoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString method;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString responseType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString redirectUri;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString scope;
};

USTRUCT(BlueprintType)
struct FAccessTokenResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString endpoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString method;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString grantType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString redirectUri;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString authHeader;
};

USTRUCT(BlueprintType)
struct FSpotifyEndpointsConfigurationResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAuthorizeResponse authorize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAccessTokenResponse accessToken;
};

USTRUCT(BlueprintType)
struct FAddUserAuthorizationsRequest
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString accessToken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int tokenExpirationTimeInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString refreshToken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString tokenGrantUtcDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString accountGuid;
};

USTRUCT(BlueprintType)
struct FSpotifyEndpointResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString access_token;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString token_type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString scope;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int expires_in;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString refresh_token;
};

USTRUCT(BlueprintType)
struct FSetDeviceRequest
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FPlayTracksRequest
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FSpotifyBaseRequest
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString accountGuid;
};