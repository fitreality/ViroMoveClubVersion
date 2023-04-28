// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Delegates/IDelegateInstance.h"
#include "GameFramework/GameStateBase.h"
#include "PGGameState.generated.h"

class ULevelStreamingDynamic;
class ASubGameState;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLevelsLoadedEvent, const TArray<ULevelStreamingDynamic*>&, LoadedLevels);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelsLoaded, const TArray<ULevelStreamingDynamic*>&, LoadedLevels);

UCLASS()
class VIROMOVE_API APGGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	APGGameState(const FObjectInitializer& InOI);

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void HandleBeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SubGameState")
	TMap<FName, TSubclassOf<ASubGameState>> GameSubStatesTemplates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubGameState")
	FName InitialGameSubStateName;

	UFUNCTION(BlueprintNativeEvent, Category = "SubGameState")
	void OnAfterBeginPlay();

	//SubStates
	UFUNCTION(BlueprintCallable, Category = "SubGameState")
	void ChangeGameSubState(FName InNewSubStateName);

	UFUNCTION(BlueprintImplementableEvent, Category = "SubGameState")
	void OnGameSubStateChanged(const FName& InSubStateName, ASubGameState* InGameSubState);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SubGameState")
	ASubGameState* GetCurrentGameSubState();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SubGameState")
	ASubGameState* GetGameSubState(FName GameSubStateName);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const override;

	UFUNCTION(BlueprintNativeEvent, Category = "GameState")
	void OnPostLogin(APlayerController* InPlayerController);

	UFUNCTION(BlueprintNativeEvent, Category = "GameState")
	void OnLogout(APlayerController* InPlayerController);

	virtual void AddPlayer(APlayerController* InPlayerController);

	virtual void RemovePlayer(APlayerController* InPlayerController);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameState")
	const TArray<APlayerController*>& GetPlayers();



	//Stream levels
	UFUNCTION(BlueprintCallable, Category = "LevelStreaming")
		void StreamLevels(const TArray<TSoftObjectPtr<UWorld>>& Levels, const TArray<FVector>& Locations, const FOnLevelsLoadedEvent& OnLevelsLoadedDelegate);

	void StreamSubLevels(const TArray<FName>& SubLevels, const TArray<FVector>& Locations);

	UFUNCTION(BlueprintCallable, Category = "LevelStreaming")
		void UnloadLevels();

	UFUNCTION(BlueprintCallable, Category = "LevelStreaming")
		void UnloadLevel(TSoftObjectPtr<UWorld> Level);

	FOnLevelsLoaded OnAllLevelsLoaded;

	UFUNCTION(BlueprintCallable, Category = "LevelStreaming")
		ULevelStreamingDynamic* StreamLevel(const TSoftObjectPtr<UWorld>& Level, const FVector& Locations, const FRotator& Rotaction);


	UFUNCTION()
		void OnLevelLoadedEvent();
protected:
	UPROPERTY()
	TMap<FName, ASubGameState*> GameSubStates;

	UPROPERTY(Transient, Replicated, ReplicatedUsing = OnRep_GameSubStatesArray)
	TArray<ASubGameState*> GameSubStatesForReplication;

	UFUNCTION()
	virtual void OnRep_GameSubStatesArray();

	UPROPERTY(Transient, Replicated, ReplicatedUsing = OnRep_GameSubStateName)
	TArray<FName> PrevAndCurrentGameSubStateName; //0 prev, 1 current

	UFUNCTION()
	virtual void OnRep_GameSubStateName();

	UPROPERTY()
	TArray<APlayerController*> Players;


	//
	UPROPERTY()
		TArray<ULevelStreamingDynamic*> LoadedLevels;

	UPROPERTY()
		TArray<ULevelStreamingDynamic*> PreviousLevels;

	int32 NumLevelsLoaded;

	UFUNCTION()
		void OnLevelLoaded(class ULevel* InLevel, class UWorld* InWorld);

	FDelegateHandle OnLevelLoadedDelegateHandle;

};
