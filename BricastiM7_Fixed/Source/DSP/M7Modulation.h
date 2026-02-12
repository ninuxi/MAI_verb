#pragma once
#include <JuceHeader.h>

class M7Modulation
{
public:
    M7Modulation();
    void prepare(double sampleRate);
    void process(float& left, float& right);
    void reset();
    
    void setRate(float rate);
    void setDepth(float depth);
    
private:
    juce::dsp::Oscillator<float> lfo1, lfo2;
    float rate = 1.0f;
    float depth = 0.3f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(M7Modulation)
};