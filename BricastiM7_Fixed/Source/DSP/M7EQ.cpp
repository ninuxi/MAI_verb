#include "M7EQ.h"

M7EQ::M7EQ() {}

void M7EQ::prepare(double sr)
{
    sampleRate = sr;
    juce::dsp::ProcessSpec spec{sampleRate, 2, 1};
    eqChain.prepare(spec);
    setLowShelf(0.0f);
    setHighShelf(0.0f);
    setMidBand(0.0f, 1000.0f);
}

void M7EQ::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    eqChain.process(context);
}

void M7EQ::reset()
{
    eqChain.reset();
}

void M7EQ::setLowShelf(float gainDb)
{
    *eqChain.get<0>().state = *juce::dsp::IIR::Coefficients<float>::makeLowShelf(
        sampleRate, 100.0f, 0.707f, juce::Decibels::decibelsToGain(gainDb)
    );
}

void M7EQ::setHighShelf(float gainDb)
{
    *eqChain.get<1>().state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(
        sampleRate, 10000.0f, 0.707f, juce::Decibels::decibelsToGain(gainDb)
    );
}

void M7EQ::setMidBand(float gainDb, float freq)
{
    *eqChain.get<2>().state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(
        sampleRate, freq, 1.0f, juce::Decibels::decibelsToGain(gainDb)
    );
}