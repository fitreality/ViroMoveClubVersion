// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Delegates/IDelegateInstance.h"
#include "GameFramework/GameStateBase.h"
#include "LevelGameState.generated.h"
class ULevelStreamingDynamic;
/**
 * 
 */

UCLASS()
class VIROMOVE_API ALevelGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "LevelStreaming")
		void StreamLevels(const TArray<TSoftObjectPtr<UWorld>>& Levels, const TArray<FVector>& Locations, const TArray<FRotator>& Rotaction);

	UFUNCTION(BlueprintCallable, Category = "LevelStreaming")
		ULevelStreamingDynamic* StreamLevel(const TSoftObjectPtr<UWorld>& Level, const FVector& Locations, const FRotator& Rotaction);


	UFUNCTION(BlueprintCallable, Category = "LevelStreaming")
		void UnloadLevels();

	UFUNCTION(BlueprintCallable, Category = "LevelStreaming")
		void UnloadLevel(ULevelStreamingDynamic* Level);

protected:

	UFUNCTION()
		void OnLevelLoaded(class ULevel* InLevel, class UWorld* InWorld);

	UFUNCTION(BlueprintCallable, Category = "LevelStreaming")
		void StreamSubLevels(const TArray<FName>& SubLevels, const TArray<FVector>& Locations);

	UPROPERTY()
		TArray<ULevelStreamingDynamic*> LoadedLevels;

	UPROPERTY()
		TArray<ULevelStreamingDynamic*> PreviousLevels;

	int32 NumLevelsLoaded;

	FDelegateHandle OnLevelLoadedDelegateHandle;

};
