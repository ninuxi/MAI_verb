#pragma once
#include <JuceHeader.h>

class EarlyReflections
{
public:
    EarlyReflections();
    void prepare(double sampleRate);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();
    
    void setLevel(float level);
    void setDecay(float decay);
    
private:
    juce::dsp::DelayLine<float> delays[8];
    float gains[8];
    float level = 0.5f;
    float decay = 0.5f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EarlyReflections)
};