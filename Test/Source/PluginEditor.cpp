/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week3PluginAudioProcessorEditor::Week3PluginAudioProcessorEditor (Week3PluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    
    
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    
    
    mSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    
    mSlider.setRange(0.f, 1.f);
    
    addAndMakeVisible(mSlider);
    
    mSlider.onValueChange  = [this](){
        DBG(mSlider.getValue());
        audioProcessor.setSineVolume(mSlider.getValue());
        
    };
    
    // new slider test
    

        
        
        
        amSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        
        
        amSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 20, 0);
        
        amSlider.setRange(0.f,1.f);
        
        addAndMakeVisible(amSlider);
        
        amSlider.onValueChange  = [this](){
            DBG(amSlider.getValue());
            audioProcessor.setSineAM(amSlider.getValue());
            
    };
    
    setSize (400, 300);
}

Week3PluginAudioProcessorEditor::~Week3PluginAudioProcessorEditor()
{
}

//==============================================================================
void Week3PluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Week3PluginAudioProcessorEditor::resized()
{
    
    mSlider.setBounds(0, 0, 150, 150);
    amSlider.setBounds(150, 0, 150, 150);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
