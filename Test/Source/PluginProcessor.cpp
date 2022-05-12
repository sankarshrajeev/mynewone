/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week3PluginAudioProcessor::Week3PluginAudioProcessor()




#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
mParameterState(*this, nullptr, "PARAMETER STATE", createParam())
#endif
{
}
 
Week3PluginAudioProcessor::~Week3PluginAudioProcessor()
{
}

//==============================================================================
const juce::String Week3PluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Week3PluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Week3PluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Week3PluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Week3PluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Week3PluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Week3PluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Week3PluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Week3PluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Week3PluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Week3PluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Week3PluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Week3PluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Week3PluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());



    static float phase = 0;
    static float phase1 = 0;
    
    for (int i =0; i< buffer.getNumSamples(); i++){
    
        float sine_1 = std::sin(phase * juce::MathConstants<float>::twoPi);
        float sine_am = std::sin(phase1 * juce::MathConstants<float>::twoPi);
        
        phase +=  442/ getSampleRate();
        //phase1 +=  6/ getSampleRate();
        phase1 +=  (100 * amSineAmt)/ getSampleRate();
        
        sine_1 *=sine_am;
        
        sine_1 *=mSineGain;
        
        buffer.setSample(0, i, sine_1);
        buffer.setSample(1, i, sine_1);
    }
}

void Week3PluginAudioProcessor::setSineVolume(float inInputVolumeAmp){
    mSineGain = inInputVolumeAmp;
}

void Week3PluginAudioProcessor::setSineAM(float inAM){
    amSineAmt = inAM;
}

//==============================================================================
bool Week3PluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Week3PluginAudioProcessor::createEditor()
{
    return new Week3PluginAudioProcessorEditor (*this);
}

//==============================================================================
void Week3PluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Week3PluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Week3PluginAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout Week3PluginAudioProcessor::createParam()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>>params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN","Gain",0.0f,0.1f,0.5f));
    
    return {params.begin(),params.end()};
}
