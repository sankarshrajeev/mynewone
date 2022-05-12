/*
  ==============================================================================

    FilterComponent.cpp
    Created: 8 May 2022 3:58:04pm
    Author:  Sankarsh Rajeev

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts,juce::String filterTypeSelectorId,juce::String filterFreqId,juce::String filterResId )
{
    juce::StringArray choices {"Low-Pass","High-Pass", "Band-Pass"};
    filterTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(filterTypeSelector);
    
    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,filterTypeSelectorId,filterTypeSelector);
    addAndMakeVisible(filterSelectorLabel);
    
    setSliderWithLabel(filterFreqSlider, filterFreqLabel, apvts, filterFreqId, filterFreqAttachment);
    setSliderWithLabel(filterResSlider, filterResLabel, apvts, filterResId, filterResAttachment);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace =bounds.removeFromTop(25.0f);
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll (juce::Colours::darkblue);

    g.setColour (juce::Colours::grey);
   // g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setFont(10.0f);
    //g.drawText("Filter", labelSpace.withX(10), juce::Justification::left);
    g.setColour (juce::Colours::white);
    //g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
    
}
void FilterComponent::resized()
{
    const auto sliderPosY =80;
    const auto startY =55;
    const auto sliderWidth = 100;
    const auto sliderHeight =90;
    const auto labelYOffset = 20;
    const auto labelHeight =20;
    filterTypeSelector.setBounds(0, 0, 90, 20);
    filterSelectorLabel.setBounds(10, startY-labelYOffset, 90, labelHeight);
    filterFreqSlider.setBounds(0, sliderPosY, sliderWidth, sliderHeight);
    filterFreqLabel.setBounds(filterFreqSlider.getX(), filterFreqSlider.getY()-labelYOffset, filterFreqSlider.getWidth(), labelHeight);
    
    filterResSlider.setBounds(filterFreqSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
    filterResLabel.setBounds(filterResSlider.getX(), filterResSlider.getY()-labelYOffset, filterResSlider.getWidth(), labelHeight);

}


using Attachment =juce::AudioProcessorValueTreeState::SliderAttachment;

void FilterComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label,juce::AudioProcessorValueTreeState&apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    
    attachment =std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts,paramID,slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(10.0f);
    
    addAndMakeVisible(label);

}
