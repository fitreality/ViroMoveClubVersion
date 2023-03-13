// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VIROMOVE_API APGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BuildInputStack(TArray<UInputComponent*>& InputStack) override;
	
	//Seamless travel
	virtual void GetSeamlessTravelActorList(bool bToEntry, TArray<AActor*>& OutActors) override;

	void AddActorToTravelList(AActor* InActor);

protected:
	TArray<AActor*> TravelActors;
};
