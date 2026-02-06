#include "M7Modulation.h"

M7Modulation::M7Modulation()
{
    lfo1.initialise([](float x) { return std::sin(x); });
    lfo2.initialise([](float x) { return std::cos(x); });
}

void M7Modulation::prepare(double sampleRate)
{
    juce::dsp::ProcessSpec spec{sampleRate, 1, 1};
    lfo1.prepare(spec);
    lfo2.prepare(spec);
    setRate(rate);
}

void M7Modulation::process(float& left, float& right)
{
    float mod1 = lfo1.processSample(0.0f) * depth;
    float mod2 = lfo2.processSample(0.0f) * depth * 0.7f;
    
    left *= (1.0f + mod1);
    right *= (1.0f + mod2);
}

void M7Modulation::reset()
{
    lfo1.reset();
    lfo2.reset();
}

void M7Modulation::setRate(float newRate)
{
    rate = newRate;
    lfo1.setFrequency(rate);
    lfo2.setFrequency(rate * 1.1f); // Slightly detuned
}

void M7Modulation::setDepth(float newDepth)
{
    depth = newDepth;
}