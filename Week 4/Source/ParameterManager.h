//
//  ParameterManager.h
//  Thisishard - Shared Code
//
//  Created by Sankarsh Rajeev on 3/12/22.
//

#ifndef ParameterManager_h
#define ParameterManager_h

#include "JuceHeader.h"
#include "ParameterDefines.h"

class ParameterManager {
public:
    
    /* */
    ParameterManager(juce::AudioProcessor* inAudioProcessor);
    
    /* */
    ~ParameterManager();
    
    /* */
    float getCurrentValue(int inParameterID);
    
    /* */
    juce::AudioProcessorValueTreeState* getValueTree();
    
private:
    
    /* this will be our "parameter tree" */
    std::unique_ptr<juce::AudioProcessorValueTreeState> mParameterState;
    
    
    std::array<std::atomic<float>*, TotalNumberParameters>mParameterValues;
};

#endif /* ParameterManager_h */
