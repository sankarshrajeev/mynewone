/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CoursePluginAudioProcessor::CoursePluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
    
}

CoursePluginAudioProcessor::~CoursePluginAudioProcessor()
{
}

//==============================================================================
const juce::String CoursePluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CoursePluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CoursePluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CoursePluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CoursePluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CoursePluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CoursePluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CoursePluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CoursePluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void CoursePluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CoursePluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize our sine wave
    mSineWave1.initialize(442, sampleRate);
    mSineWave1FMOperator.initialize(442, sampleRate);
}

void CoursePluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CoursePluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void CoursePluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    // AM STUFF
 /*
    static float phase = 0;
    static float phase1 = 0;
    
    for (int i =0; i< buffer.getNumSamples(); i++){
    
        float sine_1 = std::sin(phase * juce::MathConstants<float>::twoPi);
        float sine_am = std::sin(phase1 * juce::MathConstants<float>::twoPi);
        
        phase +=  pSineAmt/ getSampleRate();
        //phase1 +=  6/ getSampleRate();
        phase1 +=  (amSineAmt)/ getSampleRate();
        
        sine_1 *=(sine_am);
        
        sine_1 *=mSineGain;
        
        buffer.setSample(0, i, sine_1);
        buffer.setSample(1, i, sine_1);*/
        
        /* */
    
    mSineWave1FMOperator.setGain(mParameterValues[FM_AMOUNT]->load());
    mSineWave1.setGain(mParameterValues[GAIN_AMOUNT]->load());
    mParameterValues[FM_OSC_FREQ]->load();
    
    for (int sample_index = 0; sample_index < buffer.getNumSamples(); sample_index++) {
        
        float fm_operator = mSineWave1FMOperator.getNextSample();
        float output = mSineWave1.getNextSampleWithFM(fm_operator);
            
        buffer.setSample(0, sample_index, output);
        buffer.setSample(1, sample_index, output);
        
    }
}

juce::AudioProcessorValueTreeState& CoursePluginAudioProcessor::getValueTreeState()
{
    return *mParameterState.get();
}

//==============================================================================
bool CoursePluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CoursePluginAudioProcessor::createEditor()
{
    return new CoursePluginAudioProcessorEditor (*this);
}

//==============================================================================
void CoursePluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // Get the underlying ValueTree from out "Parameter Value Tree"
    auto tree_state = mParameterState->copyState();
    
    // Convert the value tree into an XML object which can be saved on disk to as binary
    std::unique_ptr<juce::XmlElement> xml(tree_state.createXml());
    
    /* */
    DBG(xml->toString());

    /* store as binary */
    copyXmlToBinary(*xml, destData);
    
}

void CoursePluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get()) {
        
        DBG(xmlState->toString());
        
        juce::ValueTree parameter_tree = juce::ValueTree::fromXml(*xmlState);
        mParameterState->replaceState(parameter_tree);
        
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CoursePluginAudioProcessor();
}
