#include "M7ReverbEngine.h"

M7ReverbEngine::M7ReverbEngine() {}

void M7ReverbEngine::prepare(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    currentBlockSize = samplesPerBlock;

    // FDN
    fdn.prepare(sampleRate, samplesPerBlock);

    // Early reflections
    earlyReflections.prepare(sampleRate, samplesPerBlock);

    // EQ
    eqProcessor.prepare(sampleRate, samplesPerBlock);

    // Pre-delay: max 500ms
    int maxPreDelaySamples = static_cast<int>(sampleRate * 0.5) + 1;
    preDelayLine.setMaximumDelayInSamples(maxPreDelaySamples);
    juce::dsp::ProcessSpec spec{sampleRate, static_cast<juce::uint32>(samplesPerBlock), 2};
    preDelayLine.prepare(spec);

    // Buffers
    dryBuffer.setSize(2, samplesPerBlock);
    wetBuffer.setSize(2, samplesPerBlock);
    erBuffer.setSize(2, samplesPerBlock);

    // Smoothed values (20ms smoothing)
    smoothMix.reset(sampleRate, 0.02);
    smoothMix.setCurrentAndTargetValue(mix);
    smoothEarlyLevel.reset(sampleRate, 0.02);
    smoothEarlyLevel.setCurrentAndTargetValue(earlyLevel);

    updateParameters();
}

void M7ReverbEngine::process(juce::AudioBuffer<float>& buffer)
{
    const int numSamples = buffer.getNumSamples();
    const int numChannels = juce::jmin(buffer.getNumChannels(), 2);

    if (numChannels < 1 || numSamples == 0)
        return;

    // Store dry signal
    for (int ch = 0; ch < numChannels; ++ch)
        dryBuffer.copyFrom(ch, 0, buffer, ch, 0, numSamples);

    // Apply pre-delay
    float preDelaySamples = preDelayMs * static_cast<float>(currentSampleRate) / 1000.0f;
    preDelayLine.setDelay(preDelaySamples);

    for (int ch = 0; ch < numChannels; ++ch)
    {
        auto* channelData = buffer.getWritePointer(ch);
        for (int i = 0; i < numSamples; ++i)
        {
            preDelayLine.pushSample(ch, channelData[i]);
            channelData[i] = preDelayLine.popSample(ch);
        }
    }

    // Copy pre-delayed signal for ER processing
    for (int ch = 0; ch < numChannels; ++ch)
        erBuffer.copyFrom(ch, 0, buffer, ch, 0, numSamples);

    // Process early reflections on erBuffer
    earlyReflections.process(erBuffer);

    // Process FDN late reverb + combine with ER
    wetBuffer.clear();

    for (int sample = 0; sample < numSamples; ++sample)
    {
        float inputL = buffer.getSample(0, sample);
        float inputR = numChannels > 1 ? buffer.getSample(1, sample) : inputL;

        float fdnOutL = 0.0f, fdnOutR = 0.0f;
        fdn.process(inputL, inputR, fdnOutL, fdnOutR);

        // Get ER output
        float erOutL = erBuffer.getSample(0, sample);
        float erOutR = numChannels > 1 ? erBuffer.getSample(1, sample) : erOutL;

        float currentEarlyLevel = smoothEarlyLevel.getNextValue();

        // Combine: ER * earlyLevel + FDN late reverb
        wetBuffer.setSample(0, sample, erOutL * currentEarlyLevel + fdnOutL);
        if (numChannels > 1)
            wetBuffer.setSample(1, sample, erOutR * currentEarlyLevel + fdnOutR);
    }

    // Apply EQ to wet signal
    eqProcessor.process(wetBuffer);

    // Mix dry and wet with smoothed mix parameter
    for (int sample = 0; sample < numSamples; ++sample)
    {
        float currentMix = smoothMix.getNextValue();

        for (int ch = 0; ch < numChannels; ++ch)
        {
            float dry = dryBuffer.getSample(ch, sample);
            float wet = wetBuffer.getSample(ch, sample);
            buffer.setSample(ch, sample, dry * (1.0f - currentMix) + wet * currentMix);
        }
    }
}

void M7ReverbEngine::reset()
{
    fdn.reset();
    earlyReflections.reset();
    eqProcessor.reset();
    preDelayLine.reset();
    dryBuffer.clear();
    wetBuffer.clear();
    erBuffer.clear();
}

void M7ReverbEngine::updateParameters()
{
    fdn.setDecayTimes(decayLow, decayMid, decayHigh);
    fdn.setDamping(dampingLow, dampingHigh);
    fdn.setSize(roomSize);
    fdn.setDiffusion(diffusionAmount);
    fdn.setModulation(modulationRate, modulationDepth);
    fdn.setFreeze(freezeActive);

    earlyReflections.setLevel(earlyLevel);
    earlyReflections.setDecay(earlyDecay);
    earlyReflections.setSize(roomSize);

    smoothMix.setTargetValue(mix);
    smoothEarlyLevel.setTargetValue(earlyLevel);
}

void M7ReverbEngine::setDecay(float low, float mid, float high)
{
    decayLow = low; decayMid = mid; decayHigh = high;
    fdn.setDecayTimes(low, mid, high);
}

void M7ReverbEngine::setPreDelay(float ms)
{
    preDelayMs = juce::jlimit(0.0f, 500.0f, ms);
}

void M7ReverbEngine::setDamping(float low, float high)
{
    dampingLow = low; dampingHigh = high;
    fdn.setDamping(low, high);
}

void M7ReverbEngine::setModulation(float rate, float depth)
{
    modulationRate = rate; modulationDepth = depth;
    fdn.setModulation(rate, depth);
}

void M7ReverbEngine::setEarlyReflections(float level, float decay)
{
    earlyLevel = level; earlyDecay = decay;
    earlyReflections.setLevel(level);
    earlyReflections.setDecay(decay);
    smoothEarlyLevel.setTargetValue(level);
}

void M7ReverbEngine::setSize(float size)
{
    roomSize = size;
    fdn.setSize(size);
    earlyReflections.setSize(size);
}

void M7ReverbEngine::setDiffusion(float diffusion)
{
    diffusionAmount = diffusion;
    fdn.setDiffusion(diffusion);
}

void M7ReverbEngine::setEQ(float lowShelf, float highShelf, float midGain, float midFreq)
{
    eqProcessor.setLowShelf(lowShelf);
    eqProcessor.setHighShelf(highShelf);
    eqProcessor.setMidBand(midGain, midFreq);
}

void M7ReverbEngine::setMix(float newMix)
{
    mix = juce::jlimit(0.0f, 1.0f, newMix);
    smoothMix.setTargetValue(mix);
}

void M7ReverbEngine::setFreeze(bool freeze)
{
    freezeActive = freeze;
    fdn.setFreeze(freeze);
}

void M7ReverbEngine::setAlgorithm(Algorithm algorithm)
{
    switch (algorithm)
    {
        case HALL_1: setDecay(3.5f, 2.8f, 1.8f); setDamping(0.3f, 0.4f); setModulation(0.8f, 0.3f); setEarlyReflections(0.6f, 0.4f); setSize(0.8f); setDiffusion(0.7f); setEQ(-2.0f, 1.5f, -1.0f, 1000.0f); break;
        case HALL_2: setDecay(4.5f, 3.5f, 2.0f); setDamping(0.3f, 0.5f); setModulation(0.7f, 0.25f); setEarlyReflections(0.5f, 0.5f); setSize(0.85f); setDiffusion(0.75f); setEQ(-1.5f, 1.0f, 0.0f, 800.0f); break;
        case HALL_3: setDecay(5.5f, 4.2f, 2.5f); setDamping(0.2f, 0.45f); setModulation(0.6f, 0.35f); setEarlyReflections(0.55f, 0.45f); setSize(0.9f); setDiffusion(0.8f); setEQ(-2.5f, 0.5f, -0.5f, 1200.0f); break;
        case HALL_4: setDecay(2.5f, 2.0f, 1.2f); setDamping(0.4f, 0.35f); setModulation(0.9f, 0.2f); setEarlyReflections(0.65f, 0.35f); setSize(0.7f); setDiffusion(0.65f); setEQ(-1.0f, 2.0f, 0.5f, 1500.0f); break;
        case HALL_5: setDecay(7.0f, 5.5f, 3.0f); setDamping(0.2f, 0.5f); setModulation(0.5f, 0.4f); setEarlyReflections(0.4f, 0.5f); setSize(0.95f); setDiffusion(0.85f); setEQ(-3.0f, 0.0f, -1.5f, 900.0f); break;
        case HALL_6: setDecay(3.0f, 2.2f, 1.5f); setDamping(0.35f, 0.3f); setModulation(1.0f, 0.3f); setEarlyReflections(0.7f, 0.3f); setSize(0.75f); setDiffusion(0.7f); setEQ(-1.5f, 2.5f, 0.0f, 2000.0f); break;
        case HALL_7: setDecay(10.0f, 8.0f, 4.0f); setDamping(0.15f, 0.55f); setModulation(0.4f, 0.45f); setEarlyReflections(0.3f, 0.6f); setSize(1.0f); setDiffusion(0.9f); setEQ(-4.0f, -1.0f, -2.0f, 800.0f); break;

        case PLATE_1: setDecay(2.5f, 1.8f, 0.9f); setDamping(0.2f, 0.6f); setModulation(1.2f, 0.5f); setEarlyReflections(0.15f, 0.2f); setSize(0.6f); setDiffusion(0.9f); setEQ(0.0f, 2.0f, 0.0f, 2000.0f); break;
        case PLATE_2: setDecay(3.5f, 2.5f, 1.2f); setDamping(0.2f, 0.55f); setModulation(1.0f, 0.45f); setEarlyReflections(0.1f, 0.15f); setSize(0.55f); setDiffusion(0.95f); setEQ(0.5f, 3.0f, 0.0f, 2500.0f); break;
        case PLATE_3: setDecay(1.8f, 1.2f, 0.7f); setDamping(0.25f, 0.5f); setModulation(1.5f, 0.55f); setEarlyReflections(0.1f, 0.1f); setSize(0.5f); setDiffusion(0.92f); setEQ(-1.0f, 1.5f, 0.5f, 3000.0f); break;
        case PLATE_4: setDecay(4.0f, 3.0f, 1.5f); setDamping(0.15f, 0.65f); setModulation(0.8f, 0.4f); setEarlyReflections(0.2f, 0.25f); setSize(0.65f); setDiffusion(0.88f); setEQ(0.0f, 1.0f, -0.5f, 1800.0f); break;
        case PLATE_5: setDecay(2.0f, 1.5f, 0.8f); setDamping(0.3f, 0.4f); setModulation(1.3f, 0.5f); setEarlyReflections(0.05f, 0.1f); setSize(0.45f); setDiffusion(0.95f); setEQ(1.0f, 4.0f, 0.0f, 4000.0f); break;

        case ROOM_1: setDecay(1.8f, 1.2f, 0.8f); setDamping(0.4f, 0.3f); setModulation(0.5f, 0.2f); setEarlyReflections(0.7f, 0.3f); setSize(0.4f); setDiffusion(0.6f); setEQ(-1.0f, 0.5f, 0.0f, 1500.0f); break;
        case ROOM_2: setDecay(1.2f, 0.8f, 0.5f); setDamping(0.5f, 0.25f); setModulation(0.4f, 0.15f); setEarlyReflections(0.8f, 0.25f); setSize(0.3f); setDiffusion(0.5f); setEQ(-0.5f, 0.0f, 0.5f, 2000.0f); break;
        case ROOM_3: setDecay(2.2f, 1.5f, 1.0f); setDamping(0.35f, 0.35f); setModulation(0.6f, 0.25f); setEarlyReflections(0.6f, 0.35f); setSize(0.5f); setDiffusion(0.65f); setEQ(-1.5f, 1.0f, -0.5f, 1200.0f); break;
        case ROOM_4: setDecay(0.8f, 0.5f, 0.3f); setDamping(0.6f, 0.2f); setModulation(0.3f, 0.1f); setEarlyReflections(0.85f, 0.2f); setSize(0.25f); setDiffusion(0.4f); setEQ(0.0f, -1.0f, 1.0f, 2500.0f); break;

        case CHAMBER_1: setDecay(2.8f, 2.0f, 1.3f); setDamping(0.35f, 0.4f); setModulation(0.7f, 0.3f); setEarlyReflections(0.5f, 0.4f); setSize(0.6f); setDiffusion(0.75f); setEQ(-1.0f, 1.5f, 0.0f, 1000.0f); break;
        case CHAMBER_2: setDecay(3.5f, 2.5f, 1.6f); setDamping(0.3f, 0.45f); setModulation(0.6f, 0.35f); setEarlyReflections(0.45f, 0.45f); setSize(0.65f); setDiffusion(0.8f); setEQ(-2.0f, 1.0f, -0.5f, 900.0f); break;
        case CHAMBER_3: setDecay(2.0f, 1.5f, 1.0f); setDamping(0.4f, 0.35f); setModulation(0.8f, 0.25f); setEarlyReflections(0.55f, 0.35f); setSize(0.55f); setDiffusion(0.7f); setEQ(-0.5f, 2.0f, 0.5f, 1500.0f); break;

        default: break;
    }
}
