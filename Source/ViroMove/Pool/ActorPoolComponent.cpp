// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPoolComponent.h"
#include "Engine/World.h"
#include "PoolableActor.h"

// Sets default values for this component's properties
UActorPoolComponent::UActorPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UActorPoolComponent::BeginPlay()
{
	Super::BeginPlay();
	//Init();
}

void UActorPoolComponent::EndPlay(const EEndPlayReason::Type InEndplayReason)
{
	Clear();

	Super::EndPlay(InEndplayReason);
}

void UActorPoolComponent::Init()
{
	for (auto It = PoolConfigs.CreateIterator(); It; ++It)
	{
		TSubclassOf<APoolableActor> ActorClass = It->Key;
		const FPoolConfig& ActorPoolConfig = It->Value;

		for (int32 i = 0; i < ActorPoolConfig.PoolSize; ++i)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			FTransform ActorTransform = ActorClass.Get()->GetDefaultObject<APoolableActor>()->GetActorTransform();
			ActorTransform.SetLocation(ActorTransform.GetLocation() + FVector(0.0f, 0.0f, -100000.0f));

			APoolableActor* SpawnedActor = GetWorld()->SpawnActor<APoolableActor>(ActorClass, ActorTransform, SpawnParams);
			if (SpawnedActor)
			{
				FPoolActorContainer& FreeItemsContainer = FreeItems.FindOrAdd(ActorClass);
				FreeItemsContainer.Items.Add(SpawnedActor);

				SpawnedActor->PoolOnActorDestroy.AddDynamic(this, &UActorPoolComponent::OnActorDestroy);
			}
		}

		TakenItems.FindOrAdd(ActorClass);
	}
}

void UActorPoolComponent::Clear()
{
	for (auto It = TakenItems.CreateIterator(); It; ++It)
	{
		FPoolActorContainer& TakenItemsContainer = It->Value;
		for (int32 i = 0; i < TakenItemsContainer.Items.Num(); ++i)
		{
			if(!TakenItemsContainer.Items[i]->IsActorBeingDestroyed())
				TakenItemsContainer.Items[i]->Destroy();
		}
	}

	for (auto It = FreeItems.CreateIterator(); It; ++It)
	{
		FPoolActorContainer& FreeItemsContainer = It->Value;
		for (int32 i = 0; i < FreeItemsContainer.Items.Num(); ++i)
		{
			if (!FreeItemsContainer.Items[i]->IsActorBeingDestroyed())
				FreeItemsContainer.Items[i]->Destroy();
		}
	}
}

void UActorPoolComponent::InitDynamic(TArray<TSubclassOf<AActor>> InActorClasses)
{
	TMap<TSubclassOf<AActor>, int32> ActorClassesMap;
	for (int32 i = 0; i < InActorClasses.Num(); ++i)
	{
		int32 PoolSize = 32;
		
		TSubclassOf<APoolableActor> PoolableActorSubclass = InActorClasses[i];
		if (FPoolConfig* PoolConfig = PoolConfigs.Find(PoolableActorSubclass))
		{
			if (PoolConfig->PoolSize > 0)
			{
				PoolSize = PoolConfig->PoolSize;
			}
		}

		ActorClassesMap.Add(InActorClasses[i], PoolSize);
	}

	for (auto It = ActorClassesMap.CreateIterator(); It; ++It)
	{
		TSubclassOf<APoolableActor> ActorClass = It->Key;
		int32 PoolSize = It->Value;

		for (int32 i = 0; i < PoolSize; ++i)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			FTransform ActorTransform = ActorClass.Get()->GetDefaultObject<APoolableActor>()->GetActorTransform();
			ActorTransform.SetLocation(ActorTransform.GetLocation() + FVector(0.0f, 0.0f, -100000.0f));

			APoolableActor* SpawnedActor = GetWorld()->SpawnActor<APoolableActor>(ActorClass, ActorTransform, SpawnParams);
			if (SpawnedActor)
			{
				FPoolActorContainer& FreeItemsContainer = FreeItems.FindOrAdd(ActorClass);
				FreeItemsContainer.Items.Add(SpawnedActor);

				SpawnedActor->PoolOnActorDestroy.AddDynamic(this, &UActorPoolComponent::OnActorDestroy);
			}
		}

		TakenItems.FindOrAdd(ActorClass);
	}
}

APoolableActor* UActorPoolComponent::GetFreeItem(TSubclassOf<APoolableActor> InActorClass)
{
	if (FreeItems.Find(InActorClass))
	{
		FPoolActorContainer& FreeItemsContainer = FreeItems[InActorClass];
		if (FreeItemsContainer.Items.Num() > 0)
		{
			APoolableActor* FreeItem = FreeItemsContainer.Items.Pop(false);
			FreeItem->OnTakenFromPool();

			TakenItems[InActorClass].Items.Add(FreeItem);

			return FreeItem;
		}
		else
		{
			//No more free items in pool //@TODO: Expand pool or take item from taken items container
			return nullptr;
		}
	}
	return nullptr;
}


void UActorPoolComponent::ReturnItem(APoolableActor* InActor)
{
	if (InActor)
	{
		TSubclassOf<APoolableActor> ActorClass = InActor->GetClass();
		if (TakenItems.Find(ActorClass))
		{
			FPoolActorContainer& TakenItemsContainer = TakenItems[ActorClass];
			int32 ItemIndex = TakenItemsContainer.Items.Find(InActor);
			if (ItemIndex != INDEX_NONE)
			{
				APoolableActor* TakenItem = TakenItemsContainer.Items[ItemIndex];
				TakenItemsContainer.Items.RemoveAt(ItemIndex, 1, false);

				TakenItem->OnReturnedToPool();

				FreeItems[ActorClass].Items.Add(TakenItem);
			}
		}
	}
}

void UActorPoolComponent::OnActorDestroy(APoolableActor* InActor)
{
	ReturnItem(InActor);
}