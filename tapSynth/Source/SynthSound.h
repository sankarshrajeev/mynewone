/*
  ==============================================================================

    SynthSound.h
    Created: 10 Apr 2022 8:05:33pm
    Author:  Sankarsh Rajeev

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
};
