/*
  ==============================================================================

    FilterData.h
    Created: 8 May 2022 1:19:21pm
    Author:  Sankarsh Rajeev

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock,int numChannels);
    void process(juce::AudioBuffer<float>&buffer);
    void updateParameters(const int filterType, const float frequency,const float resonance);
    void reset();
    
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{false};
    
    
};
