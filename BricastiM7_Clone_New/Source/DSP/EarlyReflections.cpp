#include "EarlyReflections.h"

EarlyReflections::EarlyReflections() {}

void EarlyReflections::prepare(double sampleRate)
{
    int delaysMs[8] = {13, 29, 41, 53, 67, 79, 97, 113};
    for (int i = 0; i < 8; ++i)
    {
        delays[i].prepare({sampleRate, 1, 1});
        delays[i].setMaximumDelayInSamples(sampleRate * 0.2);
        delays[i].setDelay(static_cast<float>(delaysMs[i]) * sampleRate / 1000.0f);
        gains[i] = std::pow(0.7f, i) * level;
    }
}

void EarlyReflections::process(juce::AudioBuffer<float>& buffer)
{
    const int numSamples = buffer.getNumSamples();
    
    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        auto* channel = buffer.getWritePointer(ch);
        
        for (int i = 0; i < numSamples; ++i)
        {
            float sample = channel[i];
            float early = 0.0f;
            
            for (int d = 0; d < 8; ++d)
            {
                early += delays[d].popSample(ch) * gains[d];
                delays[d].pushSample(ch, sample * decay);
            }
            
            channel[i] += early * level;
        }
    }
}

void EarlyReflections::reset()
{
    for (auto& delay : delays)
        delay.reset();
}

void EarlyReflections::setLevel(float newLevel)
{
    level = newLevel;
    for (int i = 0; i < 8; ++i)
        gains[i] = std::pow(0.7f, i) * level;
}

void EarlyReflections::setDecay(float newDecay)
{
    decay = newDecay;
}