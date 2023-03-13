// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfigFileLoad.h"
FString UConfigFileLoad::VIROtationFileString;
DEFINE_LOG_CATEGORY(ViroConfigFile);

void UConfigFileLoad::LoadConfigFile(FString &Url)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString ViroStationFile = FPaths::GameConfigDir();
	ViroStationFile.Append("URL-backend.json");
	FPaths::RemoveDuplicateSlashes(ViroStationFile);

	//FString ViroStationFile = "%AppData%/FitReality/station.json";
	if (PlatformFile.FileExists(*ViroStationFile))
	{
		FFileHelper::LoadFileToString(VIROtationFileString, *ViroStationFile);
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(VIROtationFileString);
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			Url = JsonObject->GetStringField("Url");
		}
	}
	else {
		UE_LOG(ViroConfigFile, Log, TEXT("Cannot find file: %s"), *ViroStationFile);
	}
}


