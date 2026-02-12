#include "M7ReverbEngine.h"

M7ReverbEngine::M7ReverbEngine() {}

void M7ReverbEngine::prepare(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    currentBlockSize = samplesPerBlock;
    
    fdn.prepare(sampleRate);
    earlyReflections.prepare(sampleRate);
    modulation.prepare(sampleRate);
    eqProcessor.prepare(sampleRate);
    
    dryBuffer.setSize(2, samplesPerBlock);
    wetBuffer.setSize(2, samplesPerBlock);
    
    int maxPreDelay = static_cast<int>(sampleRate * 0.5);
    preDelayBuffer.setSize(2, maxPreDelay);
    preDelayBuffer.clear();
    
    updateParameters();
}

void M7ReverbEngine::process(juce::AudioBuffer<float>& buffer)
{
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();
    
    // Store dry
    dryBuffer.makeCopyOf(buffer, true);
    
    // Apply pre-delay
    applyPreDelay(buffer);
    
    // Process early reflections
    earlyReflections.process(buffer);
    
    // Process FDN reverb
    for (int sample = 0; sample < numSamples; ++sample)
    {
        float inputL = buffer.getSample(0, sample);
        float inputR = buffer.getSample(1, sample);
        float input = (inputL + inputR) * 0.5f; // Mono input to FDN
        
        float outputL = 0.0f, outputR = 0.0f;
        fdn.process(input, outputL, outputR);
        modulation.process(outputL, outputR);
        
        wetBuffer.setSample(0, sample, outputL);
        wetBuffer.setSample(1, sample, outputR);
    }
    
    // Apply EQ
    eqProcessor.process(wetBuffer);
    
    // Mix dry and wet
    for (int ch = 0; ch < numChannels; ++ch)
    {
        buffer.copyFrom(ch, 0, dryBuffer, ch, 0, numSamples);
        buffer.applyGain(ch, 0, numSamples, 1.0f - mix);
        buffer.addFrom(ch, 0, wetBuffer, ch, 0, numSamples, mix);
    }
}

void M7ReverbEngine::applyPreDelay(juce::AudioBuffer<float>& buffer)
{
    if (preDelaySamples <= 0) return;
    
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();
    const int bufferSize = preDelayBuffer.getNumSamples();
    
    for (int ch = 0; ch < numChannels; ++ch)
    {
        auto* input = buffer.getReadPointer(ch);
        auto* delayBuffer = preDelayBuffer.getWritePointer(ch);
        
        for (int i = 0; i < numSamples; ++i)
        {
            delayBuffer[preDelayWritePos] = input[i];
            int readPos = (preDelayWritePos - preDelaySamples + bufferSize) % bufferSize;
            buffer.setSample(ch, i, delayBuffer[readPos]);
            preDelayWritePos = (preDelayWritePos + 1) % bufferSize;
        }
    }
}

void M7ReverbEngine::updateParameters()
{
    fdn.setDecayTimes(decayLow, decayMid, decayHigh);
    fdn.setDamping(dampingLow * 10000.0f, dampingHigh * 20000.0f);
    fdn.setSize(roomSize);
    fdn.setDiffusion(diffusionAmount);
    fdn.setFreeze(freezeActive);
    
    earlyReflections.setLevel(earlyLevel);
    earlyReflections.setDecay(earlyDecay);
    
    modulation.setRate(modulationRate);
    modulation.setDepth(modulationDepth);
    
    preDelaySamples = static_cast<int>(currentSampleRate * preDelayMs / 1000.0);
    preDelayReadPos = (preDelayWritePos - preDelaySamples + preDelayBuffer.getNumSamples()) % preDelayBuffer.getNumSamples();
}

void M7ReverbEngine::setDecay(float low, float mid, float high)
{
    decayLow = low; decayMid = mid; decayHigh = high;
    updateParameters();
}

void M7ReverbEngine::setPreDelay(float ms)
{
    preDelayMs = ms;
    updateParameters();
}

void M7ReverbEngine::setDamping(float low, float high)
{
    dampingLow = low; dampingHigh = high;
    updateParameters();
}

void M7ReverbEngine::setModulation(float rate, float depth)
{
    modulationRate = rate; modulationDepth = depth;
    updateParameters();
}

void M7ReverbEngine::setEarlyReflections(float level, float decay)
{
    earlyLevel = level; earlyDecay = decay;
    updateParameters();
}

void M7ReverbEngine::setSize(float size)
{
    roomSize = size;
    updateParameters();
}

void M7ReverbEngine::setDiffusion(float diffusion)
{
    diffusionAmount = diffusion;
    updateParameters();
}

void M7ReverbEngine::setEQ(float lowShelf, float highShelf, float midGain, float midFreq)
{
    eqProcessor.setLowShelf(lowShelf);
    eqProcessor.setHighShelf(highShelf);
    eqProcessor.setMidBand(midGain, midFreq);
}

void M7ReverbEngine::setMix(float newMix)
{
    mix = newMix;
}

void M7ReverbEngine::setFreeze(bool freeze)
{
    freezeActive = freeze;
    updateParameters();
}

void M7ReverbEngine::setAlgorithm(Algorithm algorithm)
{
    switch (algorithm)
    {
        case HALL_1:
            setDecay(3.5f, 2.8f, 1.8f);
            setDamping(0.7f, 0.4f);
            setModulation(0.8f, 0.3f);
            setEarlyReflections(0.6f, 0.4f);
            setSize(0.8f);
            setDiffusion(0.7f);
            setEQ(-2.0f, 1.5f, -1.0f, 1000.0f);
            break;
            
        case PLATE_1:
            setDecay(2.5f, 1.8f, 0.9f);
            setDamping(0.3f, 0.6f);
            setModulation(1.2f, 0.5f);
            setEarlyReflections(0.3f, 0.2f);
            setSize(0.6f);
            setDiffusion(0.9f);
            setEQ(0.0f, 2.0f, 0.0f, 2000.0f);
            break;
            
        case ROOM_1:
            setDecay(1.8f, 1.2f, 0.8f);
            setDamping(0.5f, 0.5f);
            setModulation(0.5f, 0.2f);
            setEarlyReflections(0.4f, 0.3f);
            setSize(0.5f);
            setDiffusion(0.6f);
            setEQ(-1.0f, 0.5f, 0.0f, 1500.0f);
            break;
            
        default:
            break;
    }
}

void M7ReverbEngine::reset()
{
    fdn.reset();
    earlyReflections.reset();
    preDelayBuffer.clear();
    preDelayWritePos = 0;
    preDelayReadPos = 0;
}