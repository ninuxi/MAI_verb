#pragma once
#include <JuceHeader.h>

class FDN4x4
{
public:
    FDN4x4();
    ~FDN4x4() = default;
    
    void prepare(double sampleRate);
    void process(float input, float& outputL, float& outputR);
    void reset();
    
    void setDecayTimes(float low, float mid, float high);
    void setDamping(float lowFreq, float highFreq);
    void setSize(float size);
    void setDiffusion(float diffusion);
    void setFreeze(bool freeze);
    
private:
    struct DelayLine
    {
        std::vector<float> buffer;
        int writePos = 0;
        int delaySamples = 0;
        
        void prepare(int maxSamples) { buffer.resize(maxSamples, 0.0f); }
        void write(float sample) { buffer[writePos] = sample; writePos = (writePos + 1) % buffer.size(); }
        float read() const { int readPos = (writePos - delaySamples + buffer.size()) % buffer.size(); return buffer[readPos]; }
        void clear() { std::fill(buffer.begin(), buffer.end(), 0.0f); writePos = 0; }
    };
    
    DelayLine delays[4];
    
    struct DampingFilter
    {
        juce::dsp::IIR::Filter<float> lowpass, highpass;
        
        void prepare(double sampleRate)
        {
            juce::dsp::ProcessSpec spec{sampleRate, 1, 1};
            lowpass.prepare(spec);
            highpass.prepare(spec);
        }
        
        float process(float sample, float lowFreq, float highFreq, double sampleRate)
        {
            *lowpass.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, lowFreq);
            *highpass.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, highFreq);
            float processed = lowpass.processSample(sample);
            return highpass.processSample(processed);
        }
    };
    
    DampingFilter dampingFilters[4];
    
    float decayTimes[3] = {3.0f, 2.0f, 1.5f};
    float dampingFreqs[2] = {1000.0f, 5000.0f};
    float roomSize = 0.7f;
    float diffusionAmount = 0.8f;
    bool freezeMode = false;
    
    float feedback[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    double currentSampleRate = 44100.0;
    
    const int primeDelays[4] = {1471, 1583, 1723, 1867};
    
    void updateDelayTimes();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FDN4x4)
};