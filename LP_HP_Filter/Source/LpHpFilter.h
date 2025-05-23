#pragma once
#include <vector>
#include "JuceHeader.h"

class LpHpFilter
{ 
public:
	void setHighpass(bool highpass);
	void setCutoffFreq(float cutoffFreq);
	void setSamplingRate(float samplingRate);

	void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);

private:
	bool highpass;
	float cutoffFreq;
	float samplingRate;
	std::vector<float> dnBuffer;
};

