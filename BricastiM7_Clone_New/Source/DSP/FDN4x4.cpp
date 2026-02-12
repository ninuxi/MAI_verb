#include "FDN4x4.h"

FDN4x4::FDN4x4() {}

void FDN4x4::prepare(double sampleRate)
{
    currentSampleRate = sampleRate;
    
    int maxDelay = static_cast<int>(sampleRate * 2.0);
    for (int i = 0; i < 4; ++i)
    {
        delays[i].prepare(maxDelay);
        dampingFilters[i].prepare(sampleRate);
    }
    
    updateDelayTimes();
}

void FDN4x4::process(float input, float& outputL, float& outputR)
{
    // Hadamard matrix for diffusion
    const float matrix[4][4] = {
        {0.5f, 0.5f, 0.5f, 0.5f},
        {0.5f, -0.5f, 0.5f, -0.5f},
        {0.5f, 0.5f, -0.5f, -0.5f},
        {0.5f, -0.5f, -0.5f, 0.5f}
    };
    
    float inputs[4] = {input * 0.25f, input * 0.25f, input * 0.25f, input * 0.25f};
    float outputs[4];
    
    for (int i = 0; i < 4; ++i)
    {
        float delayed = delays[i].read();
        
        // Apply damping
        float filtered = dampingFilters[i].process(
            delayed,
            dampingFreqs[0] * (1.0f - decayTimes[0]),
            dampingFreqs[1] * (1.0f - decayTimes[2]),
            currentSampleRate
        );
        
        // Cross feedback
        for (int j = 0; j < 4; ++j)
        {
            if (i != j)
                filtered += feedback[j] * matrix[i][j] * diffusionAmount;
        }
        
        // Add input
        filtered += inputs[i];
        
        // Apply decay
        filtered *= decayTimes[1];
        
        // Store feedback
        feedback[i] = filtered;
        
        // Write if not frozen
        if (!freezeMode)
            delays[i].write(filtered);
        
        outputs[i] = filtered;
    }
    
    // Mix to stereo
    outputL = outputs[0] + outputs[1];
    outputR = outputs[2] + outputs[3];
}

void FDN4x4::reset()
{
    for (int i = 0; i < 4; ++i)
    {
        delays[i].clear();
        feedback[i] = 0.0f;
    }
}

void FDN4x4::setDecayTimes(float low, float mid, float high)
{
    decayTimes[0] = low;
    decayTimes[1] = mid;
    decayTimes[2] = high;
}

void FDN4x4::setDamping(float lowFreq, float highFreq)
{
    dampingFreqs[0] = lowFreq;
    dampingFreqs[1] = highFreq;
}

void FDN4x4::setSize(float size)
{
    roomSize = size;
    updateDelayTimes();
}

void FDN4x4::setDiffusion(float diffusion)
{
    diffusionAmount = diffusion;
}

void FDN4x4::setFreeze(bool freeze)
{
    freezeMode = freeze;
}

void FDN4x4::updateDelayTimes()
{
    float base = 0.001f * currentSampleRate * roomSize;
    for (int i = 0; i < 4; ++i)
        delays[i].delaySamples = static_cast<int>(primeDelays[i] * base);
}