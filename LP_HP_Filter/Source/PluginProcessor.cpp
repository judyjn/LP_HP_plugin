/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include <JucePluginDefines.h>

//==============================================================================
LP_HP_FilterAudioProcessor::LP_HP_FilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#else
    :
#endif
    parameters(*this, nullptr, juce::Identifier("LpHpPlugin"), 
    {std::make_unique<juce::AudioParameterFloat>("cutoff_freq", "Cutoff_Freq", 
    juce::NormalisableRange{20.f, 20000.f, 0.1f, 0.2f, false}, 500.f),
    std::make_unique<juce::AudioParameterBool>("highpass", "HighPass", false)})
{
    cutoffFreqParam = parameters.getRawParameterValue("cutoff_freq");
    highpassParam = parameters.getRawParameterValue("highpass");
}   

LP_HP_FilterAudioProcessor::~LP_HP_FilterAudioProcessor()
{
}

//==============================================================================
const juce::String LP_HP_FilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LP_HP_FilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LP_HP_FilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LP_HP_FilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LP_HP_FilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LP_HP_FilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LP_HP_FilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LP_HP_FilterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LP_HP_FilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void LP_HP_FilterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LP_HP_FilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    filter.setSamplingRate(static_cast<float>(sampleRate));

}

void LP_HP_FilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LP_HP_FilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LP_HP_FilterAudioProcessor::processBlock (juce::AudioBuffer<float>&buffer, juce::MidiBuffer&midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    const auto cutoffFreq = cutoffFreqParam->load();
    const auto highpass = *highpassParam <0.5f ? false : true;

    filter.setCutoffFreq(cutoffFreq);
    filter.setHighpass(highpass);

    filter.processBlock(buffer, midiMessages);
}

//==============================================================================
bool LP_HP_FilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LP_HP_FilterAudioProcessor::createEditor()
{
    return new LP_HP_FilterAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void LP_HP_FilterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LP_HP_FilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LP_HP_FilterAudioProcessor();
}
