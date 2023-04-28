// Fill out your copyright notice in the Description page of Project Settings.

#include "PGGameState.h"
#include "SubGameState.h"
#include "PerfectGym.h"
#include "UnrealNetwork.h"
#include "Engine/LevelStreamingKismet.h"
#include "Engine/LevelStreaming.h"
#include "Engine/World.h"
#include "PackageName.h"
#include "Engine.h"


APGGameState::APGGameState(const FObjectInitializer& InOI) : Super(InOI)
{
	PrevAndCurrentGameSubStateName.Init(NAME_None, 2);
}

void APGGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APGGameState::BeginPlay()
{
	if (HasAuthority())
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.ObjectFlags |= RF_Transient;

		for (auto it = GameSubStatesTemplates.CreateConstIterator(); it; ++it)
		{
			const FName& SubStateName = it->Key;
			TSubclassOf<ASubGameState> GameSubStateTemplate = it->Value;
			if (GameSubStateTemplate)
			{
				ASubGameState* SpawnedGameSubState = GetWorld()->SpawnActor<ASubGameState>(GameSubStateTemplate, SpawnInfo);
				SpawnedGameSubState->Init(this);
				GameSubStates.Add(SubStateName, SpawnedGameSubState);

				GameSubStatesForReplication.Add(SpawnedGameSubState);
			}
		}
	}

	Super::BeginPlay();
}

void APGGameState::HandleBeginPlay()
{
	Super::HandleBeginPlay();

	OnAfterBeginPlay();
}

void APGGameState::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	for (auto it = GameSubStates.CreateIterator(); it; ++it)
	{
		it->Value->ConditionalBeginDestroy();
	}

	GameSubStates.Reset();
	GameSubStatesForReplication.Reset();

	Super::EndPlay(EndPlayReason);
}

void APGGameState::OnAfterBeginPlay_Implementation()
{
	for (auto it = GameSubStates.CreateIterator(); it; ++it)
	{
		it->Value->OnAfterBeginPlay();
	}
}

void APGGameState::ChangeGameSubState(FName InNewSubStateName)
{
	if (!HasAuthority())
		return;

	FName& PreviousSubStateName = PrevAndCurrentGameSubStateName[0];
	FName& CurrentSubStateName = PrevAndCurrentGameSubStateName[1];

	if (CurrentSubStateName != InNewSubStateName)
	{
		PreviousSubStateName = CurrentSubStateName;
		CurrentSubStateName = InNewSubStateName;
		OnRep_GameSubStateName();
	}
}

ASubGameState* APGGameState::GetCurrentGameSubState()
{
	if (ASubGameState** CurrentSubState = GameSubStates.Find(PrevAndCurrentGameSubStateName[1]))
	{
		return (*CurrentSubState);
	}
	return nullptr;
}

ASubGameState* APGGameState::GetGameSubState(FName SubStateName)
{
	if (ASubGameState** SubState = GameSubStates.Find(SubStateName))
	{
		return (*SubState);
	}
	return nullptr;
}

void APGGameState::OnRep_GameSubStatesArray()
{
	bool bAllStatesReplicated = true;
	for (int32 i = 0; i < GameSubStatesForReplication.Num(); ++i)
	{
		bAllStatesReplicated &= GameSubStatesForReplication[i] != nullptr;
	}

	if (bAllStatesReplicated)
	{
		int32 CurrentSubStateIdx = 0;
		for (auto it = GameSubStatesTemplates.CreateConstIterator(); it; ++it)
		{
			const FName& SubStateName = it->Key;
			GameSubStatesForReplication[CurrentSubStateIdx]->SetOwningGameState(this);
			GameSubStates.Add(SubStateName, GameSubStatesForReplication[CurrentSubStateIdx]);
			CurrentSubStateIdx++;
		}

		OnRep_GameSubStateName();
	}
}

void APGGameState::OnRep_GameSubStateName()
{
	const FName& PreviousSubStateName = PrevAndCurrentGameSubStateName[0];
	const FName& CurrentSubStateName = PrevAndCurrentGameSubStateName[1];

	if (ASubGameState** PreviousSubGameState = GameSubStates.Find(PreviousSubStateName))
	{
		(*PreviousSubGameState)->OnExit();
	}
	if (ASubGameState** NewSubGameState = GameSubStates.Find(CurrentSubStateName))
	{
		(*NewSubGameState)->OnEnter();
		OnGameSubStateChanged(CurrentSubStateName, GameSubStates[CurrentSubStateName]);
	}
}

void APGGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(APGGameState, GameSubStatesForReplication, COND_None);
	DOREPLIFETIME(APGGameState, PrevAndCurrentGameSubStateName);
}

void APGGameState::OnPostLogin_Implementation(APlayerController* InPlayerController)
{
	for (auto it = GameSubStates.CreateIterator(); it; ++it)
	{
		it->Value->OnPostLogin(InPlayerController);
	}
}

void APGGameState::OnLogout_Implementation(APlayerController* InPlayerController)
{
	for (auto it = GameSubStates.CreateIterator(); it; ++it)
	{
		it->Value->OnLogout(InPlayerController);
	}
}

void APGGameState::AddPlayer(APlayerController* InPlayerController)
{
	Players.AddUnique(InPlayerController);
}

void APGGameState::RemovePlayer(APlayerController* InPlayerController)
{
	Players.Remove(InPlayerController);
}

const TArray<APlayerController*>& APGGameState::GetPlayers()
{
	return Players;
}



void APGGameState::StreamLevels(const TArray<TSoftObjectPtr<UWorld>>& Levels, const TArray<FVector>& Locations, const FOnLevelsLoadedEvent& OnLevelsLoadedDelegate)
{
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return;
	}

	PreviousLevels = LoadedLevels;
	LoadedLevels.Reset();
	NumLevelsLoaded = 0;
	OnAllLevelsLoaded.Clear();

	bool bAllSuccess = true;
	ensure(LoadedLevels.Num() == 0);

	for (int32 i = 0; i < Levels.Num(); ++i)
	{
		if (Levels[i].GetAssetName().IsEmpty())
		{
			return;
		}

		bool bSuccess = false;
		ULevelStreamingDynamic* LoadedLevel = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(this, Levels[i], Locations[i], FRotator(0.0f, 0.0f, 0.0f), bSuccess);
		LoadedLevel->OnLevelLoaded.AddDynamic(this, &APGGameState::OnLevelLoadedEvent);
		const FString& LongPackageName = Levels[i].GetLongPackageName();
		const FString ShortPackageName = FPackageName::GetShortName(LongPackageName);
		const FString PackagePath = FPackageName::GetLongPackagePath(LongPackageName);
		FString UniqueLevelPackageName = PackagePath + TEXT("/") + ShortPackageName;
		UniqueLevelPackageName = World->RemovePIEPrefix(UniqueLevelPackageName);

		LoadedLevel->SetWorldAssetByPackageName(FName(*UniqueLevelPackageName));

		if (bSuccess)
		{
			LoadedLevels.Add(LoadedLevel);
		}
		bAllSuccess &= bSuccess;
	}

	if (bAllSuccess)
	{
		if (OnLevelLoadedDelegateHandle.IsValid())
		{
			FWorldDelegates::LevelAddedToWorld.Remove(OnLevelLoadedDelegateHandle);
		}
		OnLevelLoadedDelegateHandle = FWorldDelegates::LevelAddedToWorld.AddUObject(this, &APGGameState::OnLevelLoaded);

	}

	OnAllLevelsLoaded.Add(OnLevelsLoadedDelegate);
}

void APGGameState::StreamSubLevels(const TArray<FName>& SubLevels, const TArray<FVector>& Locations)
{
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return;
	}

	bool bAllSuccess = true;

	for (int32 i = 0; i < SubLevels.Num(); ++i)
	{
		if (!SubLevels[i].IsValid())
		{
			return;
		}

		bool bSuccess = false;
		ULevelStreamingDynamic* LoadedLevel = ULevelStreamingDynamic::LoadLevelInstance(this, SubLevels[i].ToString(), Locations[i], FRotator(0.0f, 0.0f, 0.0f), bSuccess);
		LoadedLevel->SetWorldAssetByPackageName(SubLevels[i]);

		if (bSuccess)
		{
			LoadedLevels.Add(LoadedLevel);
		}
		bAllSuccess &= bSuccess;
	}
}

void APGGameState::UnloadLevels()
{
	for (int32 i = 0; i < LoadedLevels.Num(); ++i)
	{
		ULevelStreamingDynamic* LoadedLevel = LoadedLevels[i];
		LoadedLevel->SetIsRequestingUnloadAndRemoval(true);
	}

	LoadedLevels.Reset();
	NumLevelsLoaded = 0;
}

void APGGameState::UnloadLevel(TSoftObjectPtr<UWorld> Level)
{
	int counter = LoadedLevels.IndexOfByKey(Level);
	ULevelStreamingDynamic* LoadedLevel = LoadedLevels[counter];
	LoadedLevel->SetIsRequestingUnloadAndRemoval(true);
	LoadedLevels.Remove(LoadedLevel);
}


void APGGameState::OnLevelLoaded(ULevel* InLevel, UWorld* InWorld)
{
	bool bLevelIsValid = false;
	for (int32 i = 0; i < LoadedLevels.Num(); ++i)
	{
		if (InLevel == LoadedLevels[i]->GetLoadedLevel())
		{
			bLevelIsValid = true;
			break;
		}
	}

	if (bLevelIsValid)
	{
		NumLevelsLoaded++;
		if (NumLevelsLoaded >= LoadedLevels.Num())
		{
			if (UWorld* NewWorld = Cast<UWorld>(InLevel->GetOuter()))
			{
				if (NewWorld->GetStreamingLevels().Num() > 0)
				{
					TArray<FName> SubLevels;
					TArray<FVector> SubLevelsLocations;
					for (int32 i = 0; i < NewWorld->GetStreamingLevels().Num(); ++i)
					{
						FString AssetName = "";
						AssetName.Append(NewWorld->GetStreamingLevels()[i]->GetWorldAsset().GetLongPackageName());
						AssetName = NewWorld->RemovePIEPrefix(AssetName);
						SubLevels.Add(*AssetName);
						SubLevelsLocations.Add(FVector(0.0f, 0.0f, 0.0f));
					}

					StreamSubLevels(SubLevels, SubLevelsLocations);
					return;
				}
			}

			OnAllLevelsLoaded.Broadcast(LoadedLevels);

			for (int32 i = 0; i < PreviousLevels.Num(); ++i)
			{
				ULevelStreamingKismet* PreviousLevel = PreviousLevels[i];
				PreviousLevel->SetIsRequestingUnloadAndRemoval(true);
			}
		}
	}
}

void APGGameState::OnLevelLoadedEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("APGGameState::OnLevelLoadedEvent Level is loaded"));
}


ULevelStreamingDynamic* APGGameState::StreamLevel(const TSoftObjectPtr<UWorld>& Level, const FVector& Locations, const FRotator& Rotaction)
{
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return nullptr;
	}

	PreviousLevels = LoadedLevels;
	LoadedLevels.Reset();
	NumLevelsLoaded = 0;

	bool bAllSuccess = true;
	ensure(LoadedLevels.Num() == 0);

	if (Level.GetAssetName().IsEmpty())
	{
		return nullptr;
	}

	bool bSuccess = false;
	ULevelStreamingDynamic* LoadedLevel = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(this, Level, Locations, Rotaction, bSuccess);

	const FString& LongPackageName = Level.GetLongPackageName();
	const FString ShortPackageName = FPackageName::GetShortName(LongPackageName);
	const FString PackagePath = FPackageName::GetLongPackagePath(LongPackageName);
	FString UniqueLevelPackageName = PackagePath + TEXT("/") + ShortPackageName;
	UniqueLevelPackageName = World->RemovePIEPrefix(UniqueLevelPackageName);

	LoadedLevel->SetWorldAssetByPackageName(FName(*UniqueLevelPackageName));

	if (bSuccess)
	{
		LoadedLevels.Add(LoadedLevel);
	}
	bAllSuccess &= bSuccess;

	if (bAllSuccess)
	{
		if (OnLevelLoadedDelegateHandle.IsValid())
		{
			FWorldDelegates::LevelAddedToWorld.Remove(OnLevelLoadedDelegateHandle);
		}
		return LoadedLevel;
	}
	else
	{
		return nullptr;
	}
}