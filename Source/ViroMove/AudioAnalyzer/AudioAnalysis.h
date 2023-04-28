// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <memory>
#include <functional>
#include <string>
#include "AudioAnalysis.generated.h"

enum class Endian
{
	Little, /**< LittleEndian */
	Big /**< BigEndian */
};

struct AUDIOFILE_INFO {
	int cbSize; /**< Structure size */
	unsigned int length; /**< File data size */
	uint32_t headerChunkSize; /**< Wav chunk size */
	int formatChunkOffset; /**< Offset to fmt section */
	uint32_t formatChunkSize; /**< Fmt section size */
	int16_t audioFormat; /**< Data format (PCM/ADPCM/IEEE_FLOAT) */
	int16_t numChannels; /**< Number of channels */
	uint32_t sampleRate; /**< Samples per second */
	int32_t numBytesPerSecond; /**< Bytes per second  == sampleRate * numChannels * bitDepth/8 */
	int16_t numBytesPerBlock; /**< Bytes per sample == numChannels * bitDepth/8 */
	int bitDepth; /**< Bits per sample */
	int dataChunkOffset; /**< Offset to data section */
	uint32_t dataChunkSize; /**< Samples raw data size */
	uint8* dataChunkRawData; /**< Pointer to samples raw data */
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIROMOVE_API UAudioAnalysis : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAudioAnalysis();

	UFUNCTION(BlueprintCallable)
	bool GetAudioSamplesTransforms(const FString& pathToWav, TArray<float>& totalSamples);

	UPROPERTY(BlueprintReadOnly)
	float speed;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void getAmplitude(TArray<float>& amplitude, int channel, int numTimeBands, float timeWindow, float currentTime);

	float getTotalDuration() const;

	template<typename WavType>
	void waveDataExtractor(const AUDIOFILE_INFO * audioInfo, float timeWindow, int32 &firstSample, int32 &lastSample, const uint16 &sampleIncrement, const uint32 &timeBandSize, int numTimeBands, TArray<float> & samplesByTimeBand, TArray<int32> &numSamplesByTimeband, std::function<float(uint8*, int32)> readData);


	TArray<uint8>					_rawFile;
	std::unique_ptr<AUDIOFILE_INFO> _audioInfo;

	bool loadAudioInfo(const FString& filePath);
	void moveAudioInfo(std::unique_ptr<AUDIOFILE_INFO>& destination);

	bool loadAudioInfoFromMemory(uint8* memoryPtr, unsigned int memorySize);
	int getStrOffset(uint8* dataPtr, unsigned int dataSize, std::string strToSearch);
	int32_t fourBytesToInt(uint8* dataPtr, int dataOffset, Endian endianness = Endian::Little);
	int16_t twoBytesToInt(uint8* dataPtr, int dataOffset, Endian endianness = Endian::Little);

	int channel;
	int numTimeBands;
	float timeWindow;
};
