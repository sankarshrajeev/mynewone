/*
  ==============================================================================

    AdsrData.h
    Created: 17 Apr 2022 6:12:40pm
    Author:  Sankarsh Rajeev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    
    
private:
    
    juce::ADSR::Parameters adsrParams;
};
