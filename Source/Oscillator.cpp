/*
  ==============================================================================

    Oscillator.cpp
    Created: 28 Jan 2023 1:19:59pm
    Author:  Development

  ==============================================================================
*/

#include "Oscillator.h"

namespace expressionsynth
{
    Oscillator::Oscillator()
    {
    }

    float Oscillator::WhiteNoiseGenerator()
    {
        return random.nextFloat() * 0.25 - 0.125f;
    }

    float Oscillator::SineWaveGenerator(int sample)
    {
        return sineWaveTable[sample];
    }

    void Oscillator::InitSineWavetable(double sampleRate)
    {
        increment = frequency * waveTableSize / sampleRate;

        for (size_t i = 0; i < static_cast<int>(waveTableSize); i++)
        {
            sineWaveTable.insert(i, sin(2.0 * juce::double_Pi * i / waveTableSize));
        }
    }

    float Oscillator::GetSample(int sample, float volume)
    {
        //return WhiteNoiseGenerator(volume) * volume;
        return SineWaveGenerator(sample) * volume;
    }

}