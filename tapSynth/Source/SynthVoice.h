/*
  ==============================================================================

    SynthVoice.h
    Created: 10 Apr 2022 8:05:15pm
    Author:  Sankarsh Rajeev

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber ,float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved  (int controllerNumber, int newControllerValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void update(const float attack, const float decay, const float sustain, const float release);
    OscData& getOscillator(){ return osc;  }
    
    
private:
    
    AdsrData adsr;
    juce::AudioBuffer<float> synthBuffer;
    
    OscData osc;
    //juce::dsp::Oscillator<float> osc {[](float x)  {return x < 0.0f ? -1.0f :1.0f;} };
    juce::dsp::Gain<float> gain;
    bool isPrepared{false};
    
    
    
    //return std::sin(x); //sine wav
    //return x / MathConstants<float>::pi; //saw wave
    //return x < 0.0f ? -1.0f :1.0f; //squarewave  
};
