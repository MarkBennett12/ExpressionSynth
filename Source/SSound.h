/*
  ==============================================================================

    SSound.h
    Created: 18 Mar 2023 11:39:01am
    Author:  Development

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SSound: public juce::SynthesiserSound
{
public:
    // Inherited via SynthesiserSound
    virtual bool appliesToNote(int midiNoteNumber) override;

    virtual bool appliesToChannel(int midiChannel) override;

};
