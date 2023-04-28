// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "openvr.h"
#include "SafetyActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIROMOVE_API USafetyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USafetyActorComponent();

	UFUNCTION(BlueprintCallable)
	static	void GetChaperoneRectangle(FVector& v0, FVector& v1, FVector& v2, FVector& v3);

protected:
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	vr::IVRSystem* vr_pointer;
};
