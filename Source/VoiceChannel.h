/*
  ==============================================================================

    VoiceChannel.h
    Created: 16 Mar 2023 11:41:00am
    Author:  Development

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SSound.h"

const int LOOKUPTABLESIZE = 256;

class VoiceChannel : public juce::SynthesiserVoice
{
private:
    static juce::Random random;

    juce::dsp::Oscillator<float> whiteNoiseGenerator{ whiteNoise }; // white noise
    juce::dsp::Oscillator<float> sineWaveGenerator{ sineWave, LOOKUPTABLESIZE }; // sine wave
    juce::dsp::Oscillator<float> sawWaveGenerator{ sawWave, LOOKUPTABLESIZE }; // saw wave
    juce::dsp::Oscillator<float> squareWaveGenerator{ squareWave, LOOKUPTABLESIZE }; // square wave

    juce::ADSR gainEnvelope;
    juce::ADSR::Parameters ADSRParameters;
    juce::dsp::Gain<float> gain;

    bool isPrepared = false;

    static float whiteNoise(float x);
    static float sineWave(float x);
    static float sawWave(float x);
    static float squareWave(float x);

public:

    // Inherited via SynthesiserVoice
    virtual bool canPlaySound(juce::SynthesiserSound*) override;
    virtual void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    virtual void stopNote(float velocity, bool allowTailOff) override;
    virtual void pitchWheelMoved(int newPitchWheelValue) override;
    virtual void controllerMoved(int controllerNumber, int newControllerValue) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);

    // Inherited via SynthesiserVoice
    virtual void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
};