// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AWeapon::IsLeftHandedtWeapon_Implementation(bool isLeft)
{
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::EnableShootingForDuration_Implementation(float time)
{
}

void AWeapon::DisableShootingForDuration_Implementation(float time)
{
}

void AWeapon::EnableShooting_Implementation()
{
	bcanShoot = true;
}
void AWeapon::EnableShootingLine_Implementation()
{
	bcanShoot = true;
}

void AWeapon::DisableShooting_Implementation()
{
	bcanShoot = false;
}

void AWeapon::CanShoot_Implementation()
{
}

void AWeapon::Fire_Implementation()
{
}