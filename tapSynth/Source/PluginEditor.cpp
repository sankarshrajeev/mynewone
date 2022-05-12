/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor (TapSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),osc(audioProcessor.apvts,"OSC1WAVETYPE","OSC1FMFREQ","OSC1FMDEPTH"),adsr(audioProcessor.apvts),filter(audioProcessor.apvts,"FILTERTYPE","FILTERFREQ","FILTERRES")
{
    

    setSize (800, 500);
    addAndMakeVisible(osc);
    //oscSelectAttachment= std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts,"OSC",oscSelector);
    
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(horizontalMeterL);
    addAndMakeVisible(horizontalMeterR);
    
    startTimerHz(24);
    
    
    
}

TapSynthAudioProcessorEditor::~TapSynthAudioProcessorEditor()
{
}

void TapSynthAudioProcessorEditor::timerCallback()
{
    horizontalMeterL.setLevel(audioProcessor.getRmsValue(0));
    horizontalMeterR.setLevel(audioProcessor.getRmsValue(1));
    horizontalMeterL.repaint();
    horizontalMeterR.repaint();
}

//==============================================================================
void TapSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    //getLookAndFeel()
    
   // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.fillAll (juce::Colours::darkblue);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void TapSynthAudioProcessorEditor::resized()
{
    
    const auto paddingX =5;
    const auto paddingY=35;
    const auto paddingY2=270;
    
    
    osc.setBounds(paddingX, paddingY, 300, 200);
    adsr.setBounds(getWidth()/2,0,getWidth()/2,getHeight());
    filter.setBounds(paddingX,paddingY2,300,200);
    //set bounds
    
    //meter
    
    horizontalMeterL.setBounds(200,50,200,15);
    horizontalMeterR.setBounds(200,70,200,15);
}

