// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructures/BackendTypes.h"
//#include "Runtime/Online/HTTP/Public/Http.h"
////--------HTTP & JSON includes--------
//#include "Runtime/Json/Public/Dom/JsonObject.h"
//#include "Runtime/Json/Public/Serialization/JsonReader.h"
//#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
//#include "JsonObjectConverter.h"
#include "ConfigFileLoad.h"
#include "Runtime/Online/HTTP/Public/Http.h"
//--------HTTP & JSON includes--------
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"
#include "WebCommunicationBaseComponent.generated.h"


USTRUCT(BlueprintType)
struct FCallbackBinding {
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "receiving object")
		UObject *receiver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "object's method to execute")
		FString callbackName;
};

UCLASS(abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VIROMOVE_API UWebCommunicationBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWebCommunicationBaseComponent();

	template<typename StructType>
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FCallbackBinding callbackBinding)
	{
		int code;
		FString message;
		UFunction* Function = callbackBinding.receiver->FindFunction(FName(*callbackBinding.callbackName));
		FDynamicArgsWithParameter<StructType> args;
		StructType type;
		bool isResponseValid = ResponseIsValid(Response, bWasSuccessful, code, message);
		if(isResponseValid)
			this->template GetStructFromJsonString<StructType>(Response, type);
		args.code = code;
		args.message = message;
		args.type = type;
		callbackBinding.receiver->ProcessEvent(Function, &args);
	}

	void OnResponseReceived_void(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FCallbackBinding callbackBinding)
	{
		int code;
		FString message;
		ResponseIsValid(Response, bWasSuccessful, code, message);
		FDynamicArgsVoid args;
		args.code = code;
		args.message = message;
		UFunction* Function = callbackBinding.receiver->FindFunction(FName(*callbackBinding.callbackName));
		callbackBinding.receiver->ProcessEvent(Function, &args);
	}

	void OnResponseReceived_void(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		/*int code;
		FString message;
		if (!ResponseIsValid(Response, bWasSuccessful, code, message)) return;*/
	}

	FString baseURL;

protected:

	TSharedRef<IHttpRequest> GetRequest(FString Subroute, const TMap<FString, FString> &headers, FString AdditionalContentString = "");

	TSharedRef<IHttpRequest> GetCleanRequest();

	TSharedRef<IHttpRequest> PostRequest(FString Subroute, FString ContentJsonString, const TMap<FString, FString> &headers);

	TSharedRef<IHttpRequest> PostRequestNoJson(FString Subroute, const TMap<FString, FString> &headers);


	TSharedRef<IHttpRequest> RequestWithRoute(FString Subroute, const TMap<FString, FString> &headers);

	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful, int& responseCode, FString& message);	

	bool CheckIfCallbackIsCorrect(FCallbackBinding binding, FString propType);

	template <typename StructType>
	void GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput)
	{
		FJsonObjectConverter::UStructToJsonObjectString(StructType::StaticStruct(), &FilledStruct, StringOutput, 0, 0);
	}

	template <typename StructType>
	void GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput)
	{
		FString JsonString = Response->GetContentAsString();
		FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(JsonString, &StructOutput, 0, 0);
	}

private:
	FHttpModule* Http;

	void SetRequestHeaders(TSharedRef<IHttpRequest>& Request, const TMap<FString, FString> &headers);

	template <typename StructType>
	struct FDynamicArgsWithParameter {
		int code;
		FString message;
		StructType type;
	};

	struct FDynamicArgsVoid{
		int code;
		FString message;
	};
	
};
