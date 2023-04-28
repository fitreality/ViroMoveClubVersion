// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioAnalysis.h"
#include "Misc/FileHelper.h"

// Sets default values for this component's properties
UAudioAnalysis::UAudioAnalysis()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	channel = 0;
	numTimeBands = 256;
	timeWindow = 1.0f;
	speed = numTimeBands / timeWindow;
	// ...
}


bool UAudioAnalysis::GetAudioSamplesTransforms(const FString & pathToWav, TArray<float> &totalSamples)
{
	totalSamples.Empty();

	if (loadAudioInfo(pathToWav))
		moveAudioInfo(_audioInfo);
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't load audio"));
		return false;
	}

	float currentTime = 0.0;
	float duration = getTotalDuration();
	while (currentTime < duration) {
		TArray<float> currentAnalysis;
		getAmplitude(currentAnalysis, channel, numTimeBands, timeWindow, currentTime);
		currentTime += timeWindow;
		totalSamples.Append(currentAnalysis);
	}

	return true;

	//float xSizeUnits = widthFactor;
	//float xScale = 0.01f * xSizeUnits;
	//float xPos = 0;



	//UE_LOG(LogTemp, Warning, TEXT("Total num is: %d"), totalAnalysis.Num());

	//int num = totalAnalysis.Num();
	////num = 1500;
	//for (int i = 0; i < num; i++)
	//{
	//	FTransform tr;
	//	tr.SetScale3D(FVector(xScale, 2.0f * totalAnalysis[i] * heightFactor, 1.0f));
	//	tr.SetLocation(FVector(xPos, 0, 0));
	//	xPos += xSizeUnits;
	//	instances->AddInstance(tr);
	//}

}

// Called when the game starts
void UAudioAnalysis::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAudioAnalysis::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UAudioAnalysis::loadAudioInfo(const FString& filePath)
{
	FFileHelper::LoadFileToArray(_rawFile, *filePath);
	if (_rawFile.Num() == 0) return false;
	uint8* data = _rawFile.GetData();
	unsigned int dataLength = 0;
	dataLength = _rawFile.Num() * sizeof(uint8);

	return loadAudioInfoFromMemory(data, dataLength);
}

int UAudioAnalysis::getStrOffset(uint8* dataPtr, unsigned int dataSize, std::string strToSearch)
{
	int strOffset = -1;
	int strLength = (int)strToSearch.length();

	for (unsigned int dataOffset = 0; dataOffset < (dataSize - strLength); ++dataOffset)
	{
		std::string section(dataPtr + dataOffset, dataPtr + dataOffset + strLength);

		if (section == strToSearch)
		{
			strOffset = dataOffset;
			break;
		}
	}

	return strOffset;
}

int32_t UAudioAnalysis::fourBytesToInt(uint8* dataPtr, int dataOffset, Endian endianness)
{
	int32_t result;
	if (endianness == Endian::Little)
	{
		result = (dataPtr[dataOffset + 3] << 24) |
			(dataPtr[dataOffset + 2] << 16) |
			(dataPtr[dataOffset + 1] << 8) |
			(dataPtr[dataOffset]);
	}
	else
	{
		result = (dataPtr[dataOffset] << 24) |
			(dataPtr[dataOffset + 1] << 16) |
			(dataPtr[dataOffset + 2] << 8) |
			(dataPtr[dataOffset + 3]);
	}

	return result;
}

int16_t UAudioAnalysis::twoBytesToInt(uint8* dataPtr, int dataOffset, Endian endianness)
{
	int16_t result;
	if (endianness == Endian::Little)
	{
		result = (dataPtr[dataOffset + 1] << 8) |
			(dataPtr[dataOffset]);
	}
	else
	{
		result = (dataPtr[dataOffset] << 8) |
			(dataPtr[dataOffset + 1]);
	}

	return result;
}

bool UAudioAnalysis::loadAudioInfoFromMemory(uint8* dataPtr, unsigned int dataSize)
{
	_audioInfo.reset(new AUDIOFILE_INFO);
	_audioInfo->cbSize = sizeof(*(_audioInfo.get()));
	_audioInfo->length = dataSize;

	std::string headerChunkID(dataPtr, dataPtr + 4);
	_audioInfo->headerChunkSize = (uint32_t)fourBytesToInt(dataPtr, 4);
	std::string format(dataPtr + 8, dataPtr + 12);

	_audioInfo->formatChunkOffset = getStrOffset(dataPtr, dataSize, "fmt");
	_audioInfo->dataChunkOffset = getStrOffset(dataPtr, dataSize, "data");

	if (_audioInfo->dataChunkOffset == -1 || _audioInfo->formatChunkOffset == -1 || headerChunkID != "RIFF" || format != "WAVE")
	{
		UE_LOG(LogTemp, Error, TEXT("This doesn't seem to be a valid .WAV file"));
		_audioInfo.release();
		return false;
	}

	std::string formatChunkID(dataPtr + _audioInfo->formatChunkOffset, dataPtr + _audioInfo->formatChunkOffset + 4);
	_audioInfo->formatChunkSize = (uint32_t)fourBytesToInt(dataPtr, _audioInfo->formatChunkOffset + 4);
	_audioInfo->audioFormat = twoBytesToInt(dataPtr, _audioInfo->formatChunkOffset + 8);
	_audioInfo->numChannels = twoBytesToInt(dataPtr, _audioInfo->formatChunkOffset + 10);
	_audioInfo->sampleRate = (uint32_t)fourBytesToInt(dataPtr, _audioInfo->formatChunkOffset + 12);
	_audioInfo->numBytesPerSecond = fourBytesToInt(dataPtr, _audioInfo->formatChunkOffset + 16);
	_audioInfo->numBytesPerBlock = twoBytesToInt(dataPtr, _audioInfo->formatChunkOffset + 20);
	_audioInfo->bitDepth = (int)twoBytesToInt(dataPtr, _audioInfo->formatChunkOffset + 22);

	std::string dataChunkID(dataPtr + _audioInfo->dataChunkOffset, dataPtr + _audioInfo->dataChunkOffset + 4);
	_audioInfo->dataChunkSize = (uint32_t)fourBytesToInt(dataPtr, _audioInfo->dataChunkOffset + 4);

	_audioInfo->dataChunkRawData = (dataPtr + _audioInfo->dataChunkOffset + 8);

	if (_audioInfo->numChannels < 1 || _audioInfo->numChannels > 2)
	{
		UE_LOG(LogTemp, Error, TEXT("Only support Mono and Stereo .WAV files"));
		_audioInfo.release();
		return false;
	}

	// PCM_CODE        0x0001
	// MS_ADPCM_CODE   0x0002
	// IEEE_FLOAT_CODE 0x0003
	// IMA_ADPCM_CODE  0x0011
	// MP3_CODE        0x0055 // not supported
	// EXTENSIBLE_CODE 0xFFFE

	if (_audioInfo->audioFormat != 1 && _audioInfo->audioFormat != 3)
	{
		UE_LOG(LogTemp, Error, TEXT("Format .WAV file not supported"));
		_audioInfo.release();
		return false;
	}

	if ((_audioInfo->numBytesPerSecond != (_audioInfo->numChannels * _audioInfo->sampleRate * _audioInfo->bitDepth) / 8) ||
		(_audioInfo->numBytesPerBlock != (_audioInfo->numChannels * _audioInfo->bitDepth) / 8))
	{
		UE_LOG(LogTemp, Error, TEXT("Bad .WAV header Info"));
		_audioInfo.release();
		return false;
	}

	if (_audioInfo->bitDepth != 16 && _audioInfo->bitDepth != 32)
	{
		UE_LOG(LogTemp, Error, TEXT("This file has a bit depth that is not 16 or 32 bits"));
		_audioInfo.release();
		return false;
	}
	return true;
}

void UAudioAnalysis::moveAudioInfo(std::unique_ptr<AUDIOFILE_INFO>& destination)
{
	destination = std::move(_audioInfo);
}

float fourBytesToFloat(uint8* dataPtr, int32 dataOffset)
{
	int32 result;
	result = (dataPtr[dataOffset + 3] << 24) |
		(dataPtr[dataOffset + 2] << 16) |
		(dataPtr[dataOffset + 1] << 8) |
		(dataPtr[dataOffset]);

	return result / 2147483648.0f;
}

float twoBytesToFloat(uint8* dataPtr, int32 dataOffset)
{
	int16 result;
	result = (dataPtr[dataOffset + 1] << 8) |
		(dataPtr[dataOffset]);
	return result / 32768.0f;
}

float readFloat(uint8* dataPtr, int32 dataOffset)
{
	float* resultPtr = reinterpret_cast<float*>(dataPtr + dataOffset);
	return *resultPtr;
}

void UAudioAnalysis::getAmplitude(TArray<float>& samplesByTimeBand, int channel, int numTimeBands, float timeWindow, float currentTime)
{
	samplesByTimeBand.Init(0.0, numTimeBands);
	if (numTimeBands > 0 && timeWindow > 0)
	{
		TArray<int32> numSamplesByTimeband;
		numSamplesByTimeband.Init(0, numTimeBands);
		const AUDIOFILE_INFO* audioInfo = _audioInfo.get();

		if (audioInfo)
		{
			uint32 timeBandSize = (audioInfo->sampleRate * timeWindow) / numTimeBands;

			if (timeBandSize > 0)
			{
				bool selectChannel = channel > 0 && channel <= audioInfo->numChannels;

				uint16 sampleIncrement = selectChannel ? audioInfo->numChannels : 1;
				int numSelChannel = selectChannel ? (channel - 1) : 0;

				int32 numSample = audioInfo->sampleRate * currentTime;
				int32 firstSample = (numSample * audioInfo->numChannels) + numSelChannel;
				int32 lastSample = 0;//(audioInfo->sampleRate * (currentTime + timeWindow) * audioInfo->numChannels) + numSelChannel;
				{
					//std::lock_guard<std::mutex> lock(_AACurrentSource->getSourceMutex());
					if (audioInfo->audioFormat == 1) 	// PCM_CODE        0x0001
					{
						switch (audioInfo->bitDepth)
						{
						case 16: waveDataExtractor<int16>(audioInfo, timeWindow, firstSample, lastSample, sampleIncrement, timeBandSize, numTimeBands, samplesByTimeBand, numSamplesByTimeband, twoBytesToFloat); break;
						case 32: waveDataExtractor<int32>(audioInfo, timeWindow, firstSample, lastSample, sampleIncrement, timeBandSize, numTimeBands, samplesByTimeBand, numSamplesByTimeband, fourBytesToFloat); break;
						}
					}
					else if (audioInfo->audioFormat == 3) 	// IEEE_FLOAT_CODE 0x0003
					{
						switch (audioInfo->bitDepth)
						{
						case 32: waveDataExtractor<float>(audioInfo, timeWindow, firstSample, lastSample, sampleIncrement, timeBandSize, numTimeBands, samplesByTimeBand, numSamplesByTimeband, readFloat); break;
						}
					}
				}

				for (int numTimeBand = 0; numTimeBand < numTimeBands; ++numTimeBand)
				{
					int32 numSamplesBand = numSamplesByTimeband[numTimeBand];
					if (numSamplesBand > 0)
					{
						samplesByTimeBand[numTimeBand] /= numSamplesBand;
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid Sound Info"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NumTimeBands and TimeWindow must be greater than zero"));
	}
}

float UAudioAnalysis::getTotalDuration() const
{
	const AUDIOFILE_INFO* audioInfoPtr = _audioInfo.get();
	if (audioInfoPtr)
	{
		return (audioInfoPtr->dataChunkSize / (float)(audioInfoPtr->numChannels * (audioInfoPtr->bitDepth / 8))) / audioInfoPtr->sampleRate;
	}
	return 0;
}

template<typename WavType>
void UAudioAnalysis::waveDataExtractor(const AUDIOFILE_INFO * audioInfo, float timeWindow, int32 &firstSample, int32 &lastSample, const uint16 &sampleIncrement, const uint32 &timeBandSize, int numTimeBands, TArray<float> & samplesByTimeBand, TArray<int32> &numSamplesByTimeband, std::function<float(uint8*, int32)> readData)
{
	int32 maxSampleOffest = audioInfo->dataChunkSize / (audioInfo->bitDepth / 8);

	int32 numWindowSamples = audioInfo->sampleRate * audioInfo->numChannels * timeWindow;
	if (numWindowSamples > 0)
	{
		// Center the wave
		firstSample -= (numWindowSamples / 2);
		lastSample = firstSample + (numWindowSamples * audioInfo->numChannels);
	}

	for (int32 sampleOffset = firstSample;
		sampleOffset < lastSample;
		sampleOffset += sampleIncrement)
	{
		int32 numTimeBand = (sampleOffset - firstSample) / (timeBandSize * audioInfo->numChannels);
		if (numTimeBand < numTimeBands)
		{
			if (sampleOffset < maxSampleOffest)
			{
				int32 offset = (sampleOffset * sizeof(WavType));
				if (offset > 0)
				{
					samplesByTimeBand[numTimeBand] += FMath::Abs(readData(audioInfo->dataChunkRawData, offset));
				}
			}

			numSamplesByTimeband[numTimeBand] += 1;
		}
	}
}