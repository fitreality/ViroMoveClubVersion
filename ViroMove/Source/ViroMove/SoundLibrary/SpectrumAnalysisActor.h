// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Sound/SoundWave.h"
#include "SpectrumAnalysisActor.generated.h"

// This struct contains information about the sound buffer.
struct SongBufferInfo
{
	int32 NumChannels;
	float Duration;
	int32 SampleRate;
	int32 RawPCMDataSize;

	SongBufferInfo()
		: NumChannels(0), Duration(0), SampleRate(0), RawPCMDataSize(0)
	{ }

	SongBufferInfo(int32 PCMDataSize, int32 numChannels, float duration, int32 sampleRate)
		: NumChannels(numChannels), Duration(duration), SampleRate(sampleRate), RawPCMDataSize(PCMDataSize)
	{    }
};

// this struct contains the sound buffer + information about it.
struct SongBufferData
{
	TArray<uint8> RawPCMData;
	SongBufferInfo BufferInfo;

	// default to nothing.
	SongBufferData() : SongBufferData(0, 0, 0, 0) {    }

	// allocate memory as we populate the structure.
	SongBufferData(int32 PCMDataSize, int32 numChannels, float duration, int32 sampleRate)
		: BufferInfo(PCMDataSize, numChannels, duration, sampleRate)
	{
		// create the space
		//RawPCMData = (uint8*)FMemory::Malloc(RawPCMDataSize);
		//RawPCMData = new uint8[PCMDataSize];
		RawPCMData.SetNumZeroed(PCMDataSize);
	}
};


UCLASS()
class VIROMOVE_API ASpectrumAnalysisActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpectrumAnalysisActor();

	UPROPERTY(EditAnywhere)
	USoundWave* musicTrack;

	UFUNCTION()
	void RecalculateBeat();

	UFUNCTION(BlueprintCallable)
		void DecompressAudio();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;	

	
	bool DecompressUSoundWave(USoundWave * soundWave, TSharedPtr<SongBufferData> & Out_SongBufferData);
	
	TArray<int16> pcmData16;

	int windowSize = 1024; // will be used for FFT

};
