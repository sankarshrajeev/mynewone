/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 17 Apr 2022 6:12:07pm
    Author:  Sankarsh Rajeev

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachement = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    attackAttachment = std::make_unique<SliderAttachement>(apvts,"ATTACK",attackSlider);
    decayAttachment = std::make_unique<SliderAttachement>(apvts,"DECAY",decaySlider);
    sustainAttachment = std::make_unique<SliderAttachement>(apvts,"SUSTAIN",sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachement>(apvts,"RELEASE",releaseSlider);
    
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll (juce::Colours::darkblue);

  
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth()/4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;
    
    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight()+padding,sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight()+padding,sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight()+padding,sliderStartY, sliderWidth, sliderHeight);

}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}

