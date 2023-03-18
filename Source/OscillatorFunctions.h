/*
  ==============================================================================

    OscillatorFunctions.h
    Created: 27 Feb 2023 8:18:51pm
    Author:  Development

  ==============================================================================
*/


// this is all a bit of a mess, need to find a better way
#pragma once

#include <JuceHeader.h>

static juce::Random random;

inline float sineWave(float x)
{
    return std::sin(x);
}

inline float sawWave(float x)
{
    return x / juce::MathConstants<float>::pi;
}

inline float squareWave(float x)
{
    return x < 0.0f ? -1.0f : 1.0f;
}

inline float whiteNoise(float x)
{
    return random.nextFloat();
}