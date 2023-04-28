// Fill out your copyright notice in the Description page of Project Settings.

#include "SubGameState.h"
#include "PerfectGym.h"
#include "UnrealNetwork.h"
#include "Engine/LevelStreamingKismet.h"
#include "Engine/LevelStreaming.h"
#include "Engine/World.h"
#include "PackageName.h"
#include "Engine.h"

ASubGameState::ASubGameState(const FObjectInitializer& InOI) : Super(InOI)
{
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bAlwaysRelevant = true;
	bNetLoadOnClient = false;

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetActorTickEnabled(false);
	bAllowTickBeforeBeginPlay = false;

	PrevAndCurrentSubStateName.Init(NAME_None, 2);
}

void ASubGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASubGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ASubGameState::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	for (auto it = SubStates.CreateIterator(); it; ++it)
	{
		it->Value->SetOwningGameState(nullptr);
		it->Value->SetOwningSubState(nullptr);
		it->Value->ConditionalBeginDestroy();
	}

	SubStates.Reset();

	Super::EndPlay(EndPlayReason);
}

void ASubGameState::Init(APGGameState* InOwningGameState)
{
	if (HasAuthority())
	{
		this->SetOwningGameState(InOwningGameState);

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.ObjectFlags |= RF_Transient;

		for (auto it = SubStatesTemplates.CreateConstIterator(); it; ++it)
		{
			const FName& SubStateName = it->Key;
			TSubclassOf<ASubGameState> SubStateTemplate = it->Value;
			if (SubStateTemplate)
			{
				ASubGameState* SpawnedSubState = GetWorld()->SpawnActor<ASubGameState>(SubStateTemplate, SpawnInfo);
				SpawnedSubState->SetOwningSubState(this);

				SpawnedSubState->Init(InOwningGameState);

				SubStates.Add(SubStateName, SpawnedSubState);
				SubStatesForReplication.Add(SpawnedSubState);
			}
		}
	}
}

void ASubGameState::OnAfterBeginPlay_Implementation()
{
	for (auto it = SubStates.CreateIterator(); it; ++it)
	{
		it->Value->SetOwningGameState(GetOwningGameState());
		it->Value->OnAfterBeginPlay();
	}
}

void ASubGameState::OnEnter_Implementation()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bAllowTickBeforeBeginPlay = true;
	SetActorTickEnabled(true);
}

void ASubGameState::OnExit_Implementation()
{
	if (ASubGameState* currentGameState = GetCurrentSubState())
	{
		currentGameState->OnExit();
	}

	SetActorTickEnabled(false);
	PrimaryActorTick.bCanEverTick = false;
}

APGGameState* ASubGameState::GetOwningGameState()
{
	return OwningGameState;
}

void ASubGameState::SetOwningGameState(APGGameState* InOwningGameState)
{
	OwningGameState = InOwningGameState;
}



ASubGameState* ASubGameState::GetOwningSubState()
{
	return OwningSubState;
}

void ASubGameState::SetOwningSubState(ASubGameState* InOwningSubState)
{
	OwningSubState = InOwningSubState;
}

//Substates
void ASubGameState::ChangeSubState(FName InNewSubStateName)
{
	if (!HasAuthority())
		return;

	FName& PreviousSubStateName = PrevAndCurrentSubStateName[0];
	FName& CurrentSubStateName = PrevAndCurrentSubStateName[1];

	if (CurrentSubStateName != InNewSubStateName)
	{
		PreviousSubStateName = CurrentSubStateName;
		CurrentSubStateName = InNewSubStateName;
		OnRep_SubStateName();
	}
}

ASubGameState* ASubGameState::GetCurrentSubState()
{
	if (ASubGameState** CurrentSubState = SubStates.Find(PrevAndCurrentSubStateName[1]))
	{
		return (*CurrentSubState);
	}
	return nullptr;
}

ASubGameState* ASubGameState::GetSubState(FName SubStateName)
{
	if (ASubGameState** SubState = SubStates.Find(SubStateName))
	{
		return (*SubState);
	}
	return nullptr;
}

void ASubGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASubGameState, SubStatesForReplication, COND_None);
	DOREPLIFETIME(ASubGameState, PrevAndCurrentSubStateName);
}

void ASubGameState::OnPostLogin_Implementation(APlayerController* InPlayerController)
{
	for (auto it = SubStates.CreateIterator(); it; ++it)
	{
		it->Value->OnPostLogin(InPlayerController);
	}
}

void ASubGameState::OnLogout_Implementation(APlayerController* InPlayerController)
{
	for (auto it = SubStates.CreateIterator(); it; ++it)
	{
		it->Value->OnLogout(InPlayerController);
	}
}



void ASubGameState::OnRep_SubStatesArray()
{
	bool bAllStatesReplicated = true;
	for (int32 i = 0; i < SubStatesForReplication.Num(); ++i)
	{
		bAllStatesReplicated &= SubStatesForReplication[i] != nullptr;
	}

	if (bAllStatesReplicated)
	{
		int32 CurrentSubStateIdx = 0;
		for (auto it = SubStatesTemplates.CreateConstIterator(); it; ++it)
		{
			const FName& SubStateName = it->Key;
			SubStatesForReplication[CurrentSubStateIdx]->SetOwningGameState(GetOwningGameState());
			SubStatesForReplication[CurrentSubStateIdx]->SetOwningSubState(this);
			SubStates.Add(SubStateName, SubStatesForReplication[CurrentSubStateIdx]);

			CurrentSubStateIdx++;
		}

		OnRep_SubStateName();
	}
}

void ASubGameState::OnRep_SubStateName()
{
	const FName& PreviousSubStateName = PrevAndCurrentSubStateName[0];
	const FName& CurrentSubStateName = PrevAndCurrentSubStateName[1];

	if (ASubGameState** PreviousSubState = SubStates.Find(PreviousSubStateName))
	{
		(*PreviousSubState)->OnExit();
	}
	if (ASubGameState** NewSubState = SubStates.Find(CurrentSubStateName))
	{
		(*NewSubState)->OnEnter();
		OnSubStateChanged(CurrentSubStateName, SubStates[CurrentSubStateName]);
	}
}