// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pool/PoolableActor.h"
#include "Enemy.generated.h"


class USimpleMovementComponent;

UCLASS(BlueprintType)
class VIROMOVE_API AEnemy : public APoolableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemy(const FObjectInitializer& InOI);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int lifes;
};