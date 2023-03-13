// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SubclassOf.h"
#include "ActorPoolComponent.generated.h"


class APoolableActor;

USTRUCT()
struct FPoolConfig
{
	GENERATED_USTRUCT_BODY()

public:
	FPoolConfig()
	{
		PoolSize = 0;
	}

	UPROPERTY(EditAnywhere)
	int32 PoolSize;
};

USTRUCT()
struct FPoolActorContainer
{
	GENERATED_USTRUCT_BODY()

public:
	FPoolActorContainer()
	{

	}

	UPROPERTY(EditAnywhere)
	TArray<APoolableActor*> Items;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VIROMOVE_API UActorPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActorPoolComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type InEndplayReason) override;

	void Init();
	void Clear();

	UFUNCTION(BlueprintCallable)
	void InitDynamic(TArray<TSubclassOf<AActor>> InActorClasses);

	UFUNCTION(BlueprintPure)
	APoolableActor* GetFreeItem(TSubclassOf<APoolableActor> InActorClass);

	UFUNCTION(BlueprintCallable)
	void ReturnItem(APoolableActor* InActor);

	UFUNCTION()
	void OnActorDestroy(APoolableActor* InActor);
public:
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<APoolableActor>, FPoolConfig> PoolConfigs;

protected:
	UPROPERTY()
	TMap<TSubclassOf<APoolableActor>, FPoolActorContainer> TakenItems;

	UPROPERTY()
	TMap<TSubclassOf<APoolableActor>, FPoolActorContainer> FreeItems;
};
