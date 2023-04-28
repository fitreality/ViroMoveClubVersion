// Fill out your copyright notice in the Description page of Project Settings.

#include "PoolableActor.h"

// Sets default values
APoolableActor::APoolableActor(const FObjectInitializer& OI) : Super(OI)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bTakenFromPool = false;
}

void APoolableActor::OnTakenFromPool_Implementation()
{
	//Empty
	bTakenFromPool = true;
}

void APoolableActor::OnReturnedToPool_Implementation()
{
	//Empty
}

void APoolableActor::K2_DestroyActor()
{
	if (bTakenFromPool)
	{
		PoolOnActorDestroy.Broadcast(this);
		OnDestroyed.Broadcast(this);
	}
	else
	{
		Super::K2_DestroyActor();
	}
}

