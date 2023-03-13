// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPoolOnActorDestroy, APoolableActor*, Actor);

UCLASS()
class VIROMOVE_API APoolableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APoolableActor(const FObjectInitializer& OI);

	UFUNCTION(BlueprintNativeEvent)
	void OnTakenFromPool();

	UFUNCTION(BlueprintNativeEvent)
	void OnReturnedToPool();

	FPoolOnActorDestroy PoolOnActorDestroy;

	virtual void K2_DestroyActor() override;
private:
	bool bTakenFromPool;
};
