#pragma once
#include <juce_dsp/juce_dsp.h>

/**
 * M7EQ: 3-band stereo EQ for the reverb wet signal.
 * Uses ProcessorDuplicator for proper stereo processing.
 */
class M7EQ
{
public:
    M7EQ();
    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();

    void setLowShelf(float gainDb);
    void setHighShelf(float gainDb);
    void setMidBand(float gainDb, float freq);

private:
    using StereoFilter = juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>
    >;

    juce::dsp::ProcessorChain<StereoFilter, StereoFilter, StereoFilter> eqChain;

    double sampleRate = 44100.0;
    int blockSize = 512;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(M7EQ)
};
