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
class Week3PluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Week3PluginAudioProcessorEditor (Week3PluginAudioProcessor&);
    ~Week3PluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Slider mSlider;
    juce::Slider amSlider;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Week3PluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week3PluginAudioProcessorEditor)
};
