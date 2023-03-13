// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConfigFileLoad.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(ViroConfigFile, Log, All);

/**
 * 
 */
UCLASS()
class VIROMOVE_API UConfigFileLoad : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "ConfigFile")
		static void LoadConfigFile(FString &Url);

	static FString VIROtationFileString;
};
