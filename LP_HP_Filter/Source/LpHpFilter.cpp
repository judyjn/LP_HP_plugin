#include "LpHpFilter.h"

void LpHpFilter::setHighpass(bool highpass)
{
	this->highpass = highpass;
}

void LpHpFilter::setCutoffFreq(float cutoffFreq)
{
	this->cutoffFreq = cutoffFreq;
}

void LpHpFilter::setSamplingRate(float samplingRate)
{
	this->samplingRate = samplingRate;
}
void LpHpFilter::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
	constexpr auto pi = 3.14159265359f;
	dnBuffer.resize(buffer.getNumChannels(), 0.f);
		const auto sign = highpass ? -1.f : 1.f;
		const auto tan = std::tan(pi * cutoffFreq / samplingRate);
		const auto a1 = (tan - 1.f) / (tan + 1.f);

		for (auto channel = 0; channel < buffer.getNumChannels(); channel++)
		{
			auto channelSample = buffer.getWritePointer(channel);
			for (auto i = 0; i < buffer.getNumSamples(); i++)
			{
				const auto inputSample = channelSample[i];
				const auto allpassFilteredSample = a1 * inputSample + dnBuffer[channel];
				dnBuffer[channel] = inputSample - a1 * allpassFilteredSample;
				const auto filterOutput = 0.5f * (inputSample + sign * allpassFilteredSample);
				channelSample[i] = filterOutput; 
			}
		}
}