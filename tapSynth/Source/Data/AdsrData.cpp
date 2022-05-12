/*
  ==============================================================================

    AdsrData.cpp
    Created: 17 Apr 2022 6:12:40pm
    Author:  Sankarsh Rajeev

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release =release;
    
    setParameters(adsrParams);
    
}
