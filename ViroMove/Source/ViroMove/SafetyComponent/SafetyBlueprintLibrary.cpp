// Fill out your copyright notice in the Description page of Project Settings.

#include "SafetyBlueprintLibrary.h"

#include "Engine.h"

#include "GameFramework/PlayerController.h"

#include "DrawDebugHelpers.h"

bool USafetyBlueprintLibrary::CheckIfAnyOfPlayersIsCloseEnough(TArray<FTransform> playerTransforms, float warningDistance, float& minDistance)
{
	if (playerTransforms.Num() < 2) return false;
	auto localPlayerTransform = playerTransforms[0];
	auto localPlayerPosition = localPlayerTransform.GetLocation();
	auto dist = warningDistance * warningDistance;
	float minDist = INT_MAX;
	minDistance = -1;
	bool foundPawnThatIsClose = false;
	for (size_t i = 1; i < playerTransforms.Num(); i++)
	{
		auto DistSquaredXY = FVector::DistSquaredXY(localPlayerPosition, playerTransforms[i].GetLocation());
		if (DistSquaredXY <= minDist)
			minDist = DistSquaredXY;
		if (DistSquaredXY <= dist)
			foundPawnThatIsClose = true;
	}
	minDistance = FMath::Sqrt(minDist);
	return foundPawnThatIsClose;
}

void USafetyBlueprintLibrary::SetupPlayAreasForPlayers(AActor* actor, FPlayAreaConfig config, TArray<FVector> chaperonCorners, TArray<FPlayAreaSetup>& areas)
{
	if (chaperonCorners.Num() < 4)
	{
		UE_LOG(LogTemp, Error, TEXT("Must be 4 chaperon corners"));
		return;
	}
	auto v0 = chaperonCorners[0];
	auto v1 = chaperonCorners[1];
	auto v2 = chaperonCorners[2];
	auto v3 = chaperonCorners[3];

	auto midChaperone = (v0 + v1 + v2 + v3) / 4.0f;

	auto v01 = v1 - v0;
	auto v03 = v3 - v0;

	float size1 = v01.Size();
	float size2 = v03.Size();

	float longerLength = FMath::Max(size1, size2);

	float shorterLength = FMath::Min(size1, size2);


	bool isNearlyEqual = FMath::IsNearlyEqual(longerLength, size1);

	//isNearlyEqual = reverseAttaching ? !isNearlyEqual : isNearlyEqual;

	FVector longer = isNearlyEqual ? v01 : v03;
	FVector shorter = isNearlyEqual ? v03 : v01;


	shorter.Normalize();
	longer.Normalize();


	float pX = config.playAreaSize.X;
	float pY = config.playAreaSize.Y;

	
	float maxP = FMath::Max(pX, pY);
	float minP = FMath::Min(pX, pY);
	bool isNearlyEqualp = FMath::IsNearlyEqual(maxP, pX);

	bool reverseAttaching = false;
	if (longerLength >= 1.8f * config.playAreaSize.GetMax())
	{
		reverseAttaching = true;
	}
	reverseAttaching = config.shouldReverse;


	isNearlyEqualp = reverseAttaching ? !isNearlyEqualp : isNearlyEqualp;

	float longerP = isNearlyEqualp ? pX : pY;
	float shorterP = isNearlyEqualp ? pY : pX;

	FVector offsetVector;
	int maxInOneDimmension = config.maxInOneDimmension;
	int j = 0;
	int k = 0;
	for (int i = 0; i < config.numberOfPlayers; i++)
	{
		offsetVector = j * longer*(config.offsetBetweenAreas + shorterP) + k * shorter * (config.offsetBetweenAreas + longerP);
		j++;
		if (j >= maxInOneDimmension)
		{
			j = 0;
			k++;
		}
		auto v0tmp = v0 + offsetVector;
		auto p0 = v0tmp;
		auto p1 = v0tmp + shorter * longerP;
		auto p3 = v0tmp + longer * shorterP;
		auto p2 = p1 + longer * shorterP;

		if (config.shouldRecenter)
		{
			//TODO add code for recentering play area
		}

		FVector middle = (p0 + p1 + p2 + p3) / 4.0f;
		FVector forward = reverseAttaching ? shorter : longer;
		forward.Normalize();
		FPlayAreaSetup setup;
		setup.playAreaCorners.Add(p0);
		setup.playAreaCorners.Add(p1);
		setup.playAreaCorners.Add(p2);
		setup.playAreaCorners.Add(p3);
		setup.playAreaCenter = middle;

		auto vecToCenter = midChaperone - middle;
		float dot = FVector::DotProduct(forward, vecToCenter);
		if (dot < 0) forward = -forward;
		if (!config.shouldForwardVectorBeDirectedToCenter)
			forward = -forward;

		setup.playAreaForwardVector = forward;
		areas.Add(setup);

		DrawDebugLine(actor->GetWorld(), middle, middle + forward * 100, FColor(255, 0, 0), false, 0.2f, 0, 5);
	}
	//Try doing it recursively - giloutine algorithm. WARNING: NO TIME!!!
}

bool USafetyBlueprintLibrary::IsPointInsidePolygon(const FVector& InLocation, const TArray<FVector>& InPolygon)
{
	int32 i = 0;
	int32 j = 0;
	bool Result = false;
	for (i = 0, j = InPolygon.Num() - 1; i < InPolygon.Num(); j = i++) 	{
		if ((InPolygon[i].Y > InLocation.Y) != (InPolygon[j].Y > InLocation.Y) &&
			(InLocation.X < (InPolygon[j].X - InPolygon[i].X) * (InLocation.Y - InPolygon[i].Y) / (InPolygon[j].Y - InPolygon[i].Y) + InPolygon[i].X)) 		{
			Result = !Result;
		}
	}
	return Result;
}