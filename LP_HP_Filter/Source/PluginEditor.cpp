/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LP_HP_FilterAudioProcessorEditor::LP_HP_FilterAudioProcessorEditor (LP_HP_FilterAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(cutoffFreqSlider);
    cutoffFreqSlider.setSliderStyle(
      juce::Slider::SliderStyle::LinearVertical);
    cutoffFreqAttachment.reset(
      new juce::AudioProcessorValueTreeState::SliderAttachment(
        vts, "cutoff_freq", cutoffFreqSlider));

    addAndMakeVisible(cutoffFreqLabel);
    cutoffFreqLabel.setText("Cutoff Frequency", juce::dontSendNotification);

    addAndMakeVisible(highpassButton);
    highpassAttachment.reset(
      new juce::AudioProcessorValueTreeState::ButtonAttachment(
        vts, "highpass", highpassButton));
    
    addAndMakeVisible(highpassButtonLabel);
    highpassButtonLabel.setText("HighPass", juce::dontSendNotification);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 400);
}

LP_HP_FilterAudioProcessorEditor::~LP_HP_FilterAudioProcessorEditor()
{
}

//==============================================================================
void LP_HP_FilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    
}

void LP_HP_FilterAudioProcessorEditor::resized()
{
    cutoffFreqSlider.setBounds({15, 35, 100, 300});
    cutoffFreqLabel.setBounds({cutoffFreqSlider.getX() + 30,
        cutoffFreqSlider.getY() - 30, 200, 50});
    
    highpassButton.setBounds({
      cutoffFreqSlider.getX(),
      cutoffFreqSlider.getY() + cutoffFreqSlider.getHeight() + 15,
      30, 50 });
    highpassButtonLabel.setBounds({
      cutoffFreqSlider.getX() + highpassButton.getWidth() + 15,
      highpassButton.getY(),
      cutoffFreqSlider.getWidth() - highpassButton.getWidth(),
      highpassButton.getHeight()});
}
