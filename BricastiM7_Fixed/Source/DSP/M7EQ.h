#pragma once
#include <JuceHeader.h>

class M7EQ
{
public:
    M7EQ();
    void prepare(double sampleRate);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();
    
    void setLowShelf(float gainDb);
    void setHighShelf(float gainDb);
    void setMidBand(float gainDb, float freq);
    
private:
    juce::dsp::ProcessorChain<
        juce::dsp::IIR::Filter<float>, // Low shelf
        juce::dsp::IIR::Filter<float>, // High shelf
        juce::dsp::IIR::Filter<float>  // Mid band
    > eqChain;
    
    double sampleRate = 44100.0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(M7EQ)
};