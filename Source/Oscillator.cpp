/*
  ==============================================================================

    Oscillator.cpp
    Created: 28 Jan 2023 1:19:59pm
    Author:  Development

  ==============================================================================
*/

#include "Oscillator.h"

float Oscillator::GetSample(float volume)
{
    return random.nextFloat() * volume - 0.125f;
}
