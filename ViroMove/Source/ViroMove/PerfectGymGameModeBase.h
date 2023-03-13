// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PerfectGymGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VIROMOVE_API APerfectGymGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:	

	virtual void PostLogin(APlayerController* InNewPlayer) override;

	virtual void Logout(AController* InExiting) override;
};
