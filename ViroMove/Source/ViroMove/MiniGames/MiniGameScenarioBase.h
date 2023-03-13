// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiniGameScenarioBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScenarioStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScenarioEnded);

USTRUCT(BlueprintType)
struct FSyncBeat {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float audioStartTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float distanceInUnits;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float distanceInBpm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float beatsPerMinute;
};

UCLASS(abstract, BlueprintType)
class VIROMOVE_API AMiniGameScenarioBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AMiniGameScenarioBase();
	UFUNCTION(BlueprintCallable, Category = "Scenario")
	void Start();
	UFUNCTION(BlueprintCallable, Category = "Scenario")
	void End();
	UFUNCTION(BlueprintCallable, Category = "Scenario")
	void SetScenarioDuration(float lifeSpan);
	UFUNCTION(BlueprintCallable, Category = "Scenario")
	AMiniGameScenarioBase* GetScenario() { return this; }

	UFUNCTION(BlueprintCallable)
	FSyncBeat GetSyncBeatInfo() const { 
		//UE_LOG(LogTemp, Warning, TEXT("GetSyncBeatInfo Name: %s"), *GetName());
		return SyncBeatStructure; 
	}

	UPROPERTY(BlueprintAssignable, Category = "Scenario")
	FOnScenarioStarted OnScenarioStarted;
	UPROPERTY(BlueprintAssignable, Category = "Scenario")
	FOnScenarioEnded OnScenarioEnded;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSyncBeat SyncBeatStructure;

	/*Scenario duration in seconds. Value <= 0 means that scenario will last untill End function is called*/
	UPROPERTY(EditAnywhere, Category = "Scenario")
	float scenarioLifeSpan;

	float difficulty;
};
