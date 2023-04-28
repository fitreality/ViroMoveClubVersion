// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS(BlueprintType, abstract)
class VIROMOVE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IFireable Interface")
		void Fire();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IFireable Interface")
		void CanShoot();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IFireable Interface")
		void DisableShooting();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IFireable Interface")
		void EnableShooting();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IFireable Interface")
		void EnableShootingLine();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IFireable Interface")
		void DisableShootingForDuration(float time);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IFireable Interface")
		void EnableShootingForDuration(float time);

	virtual void EnableShootingForDuration_Implementation(float time);
	virtual void DisableShootingForDuration_Implementation(float time);
	virtual void EnableShooting_Implementation();
	virtual void EnableShootingLine_Implementation();
	virtual void DisableShooting_Implementation();
	virtual void CanShoot_Implementation();
	virtual void Fire_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon")
	void IsLeftHandedtWeapon(bool isLeft);

	virtual void IsLeftHandedtWeapon_Implementation(bool isLeft);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	bool bcanShoot;
};
