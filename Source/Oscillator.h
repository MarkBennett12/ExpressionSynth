/*
  ==============================================================================

    Oscillator.h
    Created: 28 Jan 2023 1:19:59pm
    Author:  Development

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace expressionsynth
{
    class Oscillator
    {
    private:
        // wavetable varaibles
        double waveTableSize = 1024;
        double frequency = 440; // middle A
        double phase = 0;
        double increment = 0;

        juce::Random random;

        juce::Array<float> sineWaveTable;

        float WhiteNoiseGenerator();
        float SineWaveGenerator(int sample);

    public:
        Oscillator();
        void InitSineWavetable(double sampleRate);
        float GetSample(int sample, float volume);

    };
}
