// Fill out your copyright notice in the Description page of Project Settings.

#include "PerfectGymGameModeBase.h"
#include "PGGameState.h"

void APerfectGymGameModeBase::PostLogin(APlayerController* InNewPlayer)
{
	Super::PostLogin(InNewPlayer);

	APGGameState* GameState = GetGameState<APGGameState>();
	if (GameState)
	{
		GameState->AddPlayer(InNewPlayer);
		GameState->OnPostLogin(InNewPlayer);
	}
}

void APerfectGymGameModeBase::Logout(AController* InExiting)
{
	APGGameState* GameState = GetGameState<APGGameState>();
	if (GameState)
	{
		APlayerController* ExitingPC = Cast<APlayerController>(InExiting);

		GameState->OnLogout(ExitingPC);
		GameState->RemovePlayer(ExitingPC);
	}
}