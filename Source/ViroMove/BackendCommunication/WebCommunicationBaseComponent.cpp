// Fill out your copyright notice in the Description page of Project Settings.

#include "WebCommunicationBaseComponent.h"

// Sets default values for this component's properties
UWebCommunicationBaseComponent::UWebCommunicationBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	Http = &FHttpModule::Get();
	// ...
	baseURL = "https://fitnessgame-api-prod.viro.fit/api/"; //prod
	//baseURL = "https://fitnessgame-api-testing.viro.fit/api/"; //test
	//baseURL = "http://viro-demo.westeurope.cloudapp.azure.com:6001/api/"; //demo
}


TSharedRef<IHttpRequest> UWebCommunicationBaseComponent::GetRequest(FString Subroute, const TMap<FString, FString> &headers, FString AdditionalContentString) {
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute, headers);
	Request->SetVerb("GET");
	if (!AdditionalContentString.IsEmpty())
		Request->SetContentAsString(AdditionalContentString);
	return Request;
}

TSharedRef<IHttpRequest> UWebCommunicationBaseComponent::GetCleanRequest()
{
	return Http->CreateRequest();
}

TSharedRef<IHttpRequest> UWebCommunicationBaseComponent::PostRequest(FString Subroute, FString ContentJsonString, const TMap<FString, FString> &headers) {
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute, headers);
	Request->SetVerb("POST");
	Request->SetContentAsString(ContentJsonString);
	return Request;
}

TSharedRef<IHttpRequest> UWebCommunicationBaseComponent::PostRequestNoJson(FString Subroute, const TMap<FString, FString> &headers) {
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute, headers);
	Request->SetVerb("POST");
	return Request;
}


TSharedRef<IHttpRequest> UWebCommunicationBaseComponent::RequestWithRoute(FString Subroute, const TMap<FString, FString> &headers) {
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	//UE_LOG(LogTemp, Warning, TEXT("TESTAS URL1 %"), *baseURL);
	Request->SetURL(baseURL + Subroute);
	//UE_LOG(LogTemp, Warning, TEXT("TESTAS URL %"),*Request->GetURL());
	SetRequestHeaders(Request, headers);
	return Request;
}

void UWebCommunicationBaseComponent::SetRequestHeaders(TSharedRef<IHttpRequest>& Request, const TMap<FString, FString> &headers)
{	
	for (const TPair<FString, FString>& pair : headers)
	{
		pair.Key;
		pair.Value;
		Request->SetHeader(pair.Key, pair.Value);
	}
	//Request->SetHeader(TEXT("SuperSecretToken"), TEXT("36210277-5086-49BE-87B5-0C5CA7A037CF-8D36051B-B0F1-4D41-BAC2-CC39529D5E55"));
	//Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	//Request->SetHeader(TEXT("Authorization"), TEXT("Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJodHRwOi8vc2NoZW1hcy5taWNyb3NvZnQuY29tL3dzLzIwMDgvMDYvaWRlbnRpdHkvY2xhaW1zL3VzZXJkYXRhIjoiZTIzMjQxZTMtMWExMS00YmY0LTk1YTEtY2Y2ZmRmOWUzZDU0IiwibmJmIjoxNTU5MDQzMzczLCJleHAiOjE1NTk2NDgxNzMsImlhdCI6MTU1OTA0MzM3M30.KOlXWwP6uYivuuM-DYreTTx7ilRYO4tDEOZMaldrd0U"));*/
		
}

bool UWebCommunicationBaseComponent::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful, int& responseCode, FString& message)
{
	if (!Response.IsValid())
	{
		responseCode = -1;
		message = "Responose is not valid. Maybe server is dead";
		return false;
	}
	if (!bWasSuccessful)
	{
		responseCode = Response->GetResponseCode();
		message = "Responose was not successful";
		return false;
	}
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		responseCode = Response->GetResponseCode();
		message = "Responose is OK";
		return true;
	}
	responseCode = Response->GetResponseCode();
	message = Response->GetContentAsString();
	return false;
}

bool UWebCommunicationBaseComponent::CheckIfCallbackIsCorrect(FCallbackBinding binding, FString propType)
{
	auto target = binding.receiver;
	if (!target)
	{
		UE_LOG(LogTemp, Error, TEXT("UBackendCommunicationComponent::CheckIfCallbackIsCorrect - Receiver is null"));
		return false;
	}
	auto functionName = binding.callbackName;

	if (!target->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("UBackendCommunicationComponent::CheckIfCallbackIsCorrect - Receiver not found for '%s'"), *target->GetName());
		return false;
	}

	UFunction* Function = target->FindFunction(FName(*functionName));
	if (Function == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UBackendCommunicationComponent::CheckIfCallbackIsCorrect - function not found '%s'"), *functionName);
		return false;
	}

	TFieldIterator<UProperty> Iterator(Function);
	TArray<UProperty*> Properties;
	bool areTypesOk = true;
	FString wrongType = "";
	while (Iterator && (Iterator->PropertyFlags & CPF_Parm))
	{
		UProperty* Prop = *Iterator;
		FString type = Prop->GetCPPType();
		Properties.Add(Prop);
		++Iterator;
	}

	if (Properties.Num() < 2)
	{
		UE_LOG(LogTemp, Error, TEXT("UBackendCommunicationComponent::CheckIfCallbackIsCorrect - too few inputs. There should at least two inputs: int32, FString"));
		return false;
	}

	if (Properties.Num() > 3)
	{
		UE_LOG(LogTemp, Error, TEXT("UBackendCommunicationComponent::CheckIfCallbackIsCorrect - too many inputs"));
		return false;
	}

	FString firstProperty = Properties[0]->GetCPPType();
	FString secondProperty = Properties[1]->GetCPPType();
	areTypesOk = firstProperty.Equals("int32") && secondProperty.Equals("FString");

	if (!areTypesOk)
	{
		UE_LOG(LogTemp, Error, TEXT("UBackendCommunicationComponent::CheckIfCallbackIsCorrect - inputs are wrong. First should be int32, second should be FString"));
		return false;
	}

	bool bNoFunctionParams = Properties.Num() == 2;
	if (bNoFunctionParams && propType == "void") return true;	
	
	FString thirdProperty = Properties[2]->GetCPPType();
	areTypesOk = areTypesOk && thirdProperty.Equals(propType);

	if (!areTypesOk)
	{
		UE_LOG(LogTemp, Error, TEXT("UBackendCommunicationComponent::CheckIfCallbackIsCorrect - callback should have parameters: int, string, %s. Currently are: %s, %s, %s"), *propType, *firstProperty, *secondProperty, *thirdProperty);
	}

	return areTypesOk;
}
