/*
  ==============================================================================

    Oscillator.h
    Created: 28 Jan 2023 1:19:59pm
    Author:  Development

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Oscillator
{
private:
    juce::Random random;
    float WhiteNoiseGenerator(float volume);

public:
    float GetSample(float volume);

};