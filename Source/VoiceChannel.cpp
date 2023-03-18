/*
  ==============================================================================

    VoiceChannel.cpp
    Created: 16 Mar 2023 11:41:00am
    Author:  Development

  ==============================================================================
*/

#include "VoiceChannel.h"

juce::Random VoiceChannel::random;

float VoiceChannel::whiteNoise(float x)
{
    return random.nextFloat();
}

float VoiceChannel::sineWave(float x)
{
    return std::sin(x);
}

float VoiceChannel::sawWave(float x)
{
    return x / juce::MathConstants<float>::pi;
}

float VoiceChannel::squareWave(float x)
{
    return x < 0.0f ? -1.0f : 1.0f;
}

bool VoiceChannel::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void VoiceChannel::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    sineWaveGenerator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    sawWaveGenerator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    squareWaveGenerator.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));

    gainEnvelope.noteOn();
}

void VoiceChannel::stopNote(float velocity, bool allowTailOff)
{
    gainEnvelope.noteOff();
}

void VoiceChannel::pitchWheelMoved(int newPitchWheelValue)
{
}

void VoiceChannel::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void VoiceChannel::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    juce::dsp::ProcessSpec processSpec;

    processSpec.maximumBlockSize = samplesPerBlock;
    processSpec.sampleRate = sampleRate;
    processSpec.numChannels = numChannels;

    whiteNoiseGenerator.prepare(processSpec);
    sineWaveGenerator.prepare(processSpec);
    sawWaveGenerator.prepare(processSpec);
    squareWaveGenerator.prepare(processSpec);

    gain.prepare(processSpec); 
    gain.setGainLinear(0.5f);
    gainEnvelope.setSampleRate(sampleRate);

    isPrepared = true;
}

void VoiceChannel::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };

    whiteNoiseGenerator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    sineWaveGenerator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    sawWaveGenerator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    squareWaveGenerator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gainEnvelope.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}
