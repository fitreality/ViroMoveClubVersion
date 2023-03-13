// Fill out your copyright notice in the Description page of Project Settings.

#include "SpectrumAnalysisActor.h"
#include "Engine.h"
#include "Runtime/Engine/Public/AudioDevice.h"
#include "Runtime/Engine/Public/AudioDecompress.h"
#include "Developer/TargetPlatform/Public/Interfaces/IAudioFormat.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ASpectrumAnalysisActor::ASpectrumAnalysisActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASpectrumAnalysisActor::RecalculateBeat()
{
}

// Called when the game starts or when spawned
void ASpectrumAnalysisActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpectrumAnalysisActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpectrumAnalysisActor::DecompressAudio()
{
	TSharedPtr<SongBufferData> Out_SongBufferData;
	DecompressUSoundWave(musicTrack, Out_SongBufferData);
	//here pcm int16 data is avaiable
	//now we have to apply FFT to chenge from time to freqency domain
}

bool ASpectrumAnalysisActor::DecompressUSoundWave(USoundWave * soundWave, TSharedPtr<SongBufferData>& Out_SongBufferData)
{
	FAudioDevice * audioDevice = GetWorld() ? GetWorld()->GetAudioDevice() : nullptr;

	if (!audioDevice)
		return false;

	if (!soundWave)
		return false;

	if (soundWave->GetName() == TEXT("None"))
		return false;

	bool breturn = false;

	// erase whatever was previously here.
	Out_SongBufferData = nullptr;

	// ensure we have the sound data. compressed format is fine
	soundWave->InitAudioResource(audioDevice->GetRuntimeFormat(soundWave));

	// create a decoder for this audio. we want the PCM data.
	ICompressedAudioInfo* AudioInfo = audioDevice->CreateCompressedAudioInfo(soundWave);

	// decompress complete audio to this buffer 
	FSoundQualityInfo QualityInfo = { 0 };
	if (AudioInfo->ReadCompressedInfo(soundWave->ResourceData, soundWave->ResourceSize, &QualityInfo))
	{
		Out_SongBufferData = TSharedPtr<SongBufferData>(new SongBufferData(QualityInfo.SampleDataSize,
			QualityInfo.NumChannels,
			QualityInfo.Duration,
			QualityInfo.SampleRate));

		// Decompress all the sample data into preallocated memory now
		AudioInfo->ExpandFile(Out_SongBufferData->RawPCMData.GetData(), &QualityInfo);
		int maxAbsValue = 0;
		for (size_t i = 0; i < Out_SongBufferData->RawPCMData.Num() - 1; i+=2)
		{			
			uint16_t wd = ((uint16_t)Out_SongBufferData->RawPCMData[i+1] << 8) | Out_SongBufferData->RawPCMData[i];
			auto ab = FMath::Abs(wd);
			if(ab > maxAbsValue) 				
			pcmData16.Add(wd);
		}
		breturn = true;
	}
	UE_LOG(LogTemp, Warning, TEXT("number of samples: %d, %d, %d"), Out_SongBufferData->RawPCMData.Num(), sizeof(int16), sizeof(uint8));
	UE_LOG(LogTemp, Warning, TEXT("number of samples: %d"), pcmData16.Num());
	// clean up.
	delete AudioInfo;
	return breturn;
}

