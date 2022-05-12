/*
  ==============================================================================

    AdsrComponent.h
    Created: 17 Apr 2022 6:12:07pm
    Author:  Sankarsh Rajeev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    void setSliderParams(juce::Slider& slider);
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    
    using SliderAttachement = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachement> attackAttachment;
    std::unique_ptr<SliderAttachement> decayAttachment;
    std::unique_ptr<SliderAttachement> sustainAttachment;
    std::unique_ptr<SliderAttachement> releaseAttachment;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
