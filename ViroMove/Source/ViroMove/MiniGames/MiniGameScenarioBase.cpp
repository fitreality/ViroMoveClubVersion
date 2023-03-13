// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniGameScenarioBase.h"


// Sets default values
AMiniGameScenarioBase::AMiniGameScenarioBase() : scenarioLifeSpan(-1.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	//UE_LOG(LogTemp, Warning, TEXT("AMiniGameScenarioBase::AMiniGameScenarioBase"));
}

// Called when the game starts or when spawned
void AMiniGameScenarioBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMiniGameScenarioBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMiniGameScenarioBase::Destroyed()
{
	OnScenarioEnded.Broadcast();
}

void AMiniGameScenarioBase::Start()
{
	//UE_LOG(LogTemp, Warning, TEXT("AMiniGameScenarioBase::Start() - %f"), scenarioLifeSpan);
	SetLifeSpan(scenarioLifeSpan);
	OnScenarioStarted.Broadcast();
}

void AMiniGameScenarioBase::End()
{
	Destroy();
}

void AMiniGameScenarioBase::SetScenarioDuration(float lifeSpan)
{
	//UE_LOG(LogTemp, Error, TEXT("AMiniGameScenarioBase::SetScenarioDuration() - %f"), lifeSpan);
	this->scenarioLifeSpan = lifeSpan;
}

//void AMiniGameScenarioBase::OnScenarioStarted()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Scenario has started"));
//}
//
//void AMiniGameScenarioBase::OnScenarioEnded()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Scenario has finished"));
//}
