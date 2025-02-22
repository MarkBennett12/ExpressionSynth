/*
  ==============================================================================

    SVoice.cpp
    Created: 16 Mar 2023 11:41:00am
    Author:  Development

  ==============================================================================
*/

#include "SVoice.h"

juce::Random SVoice::random;

float SVoice::whiteNoise(float x)
{
    return random.nextFloat();
}

float SVoice::sineWave(float x)
{
    return std::sin(x);
}

// not sure about this
float SVoice::sawWave(float x)
{
    return (1/juce::MathConstants<float>::halfPi) * juce::MathConstants<float>::halfPi - std::abs(fmod(x, juce::MathConstants<float>::pi) - juce::MathConstants<float>::halfPi);
}

float SVoice::triangleWave(float x)
{
    return x / juce::MathConstants<float>::pi;
}

float SVoice::squareWave(float x)
{
    return x < 0.0f ? -1.0f : 1.0f;
}

bool SVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    sineWaveGenerator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    //squareWaveGenerator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    //sawWaveGenerator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    //triangleWaveGenerator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));

    gainEnvelope.noteOn();
}

void SVoice::stopNote(float velocity, bool allowTailOff)
{
    gainEnvelope.noteOff();
}

void SVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    juce::dsp::ProcessSpec processSpec;

    processSpec.maximumBlockSize = samplesPerBlock;
    processSpec.sampleRate = sampleRate;
    processSpec.numChannels = numChannels;

    sineWaveGenerator.prepare(processSpec);
    squareWaveGenerator.prepare(processSpec);
    sawWaveGenerator.prepare(processSpec);
    triangleWaveGenerator.prepare(processSpec);
    whiteNoiseGenerator.prepare(processSpec);

    sineGain.prepare(processSpec); 
    sineGain.setGainLinear(0.75f);
    gainEnvelope.setSampleRate(sampleRate);

    isPrepared = true;
}

void SVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };

    //calculate gain for each oscillator

    sineWaveGenerator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    //squareWaveGenerator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    //sawWaveGenerator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    //triangleWaveGenerator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    //whiteNoiseGenerator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    voiceGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gainEnvelope.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}
