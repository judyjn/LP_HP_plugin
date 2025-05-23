/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LP_HP_FilterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LP_HP_FilterAudioProcessorEditor (LP_HP_FilterAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~LP_HP_FilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LP_HP_FilterAudioProcessor& audioProcessor;
    juce::Slider cutoffFreqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      cutoffFreqAttachment;
    juce::Label cutoffFreqLabel;

    juce::ToggleButton highpassButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
      highpassAttachment;
    juce::Label highpassButtonLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LP_HP_FilterAudioProcessorEditor)
};
