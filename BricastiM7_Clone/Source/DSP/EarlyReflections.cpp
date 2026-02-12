#include "EarlyReflections.h"

// Tap times in milliseconds - Left channel
const float EarlyReflections::tapTimesL[NUM_TAPS] = {
    3.5f,  7.1f,  11.2f, 15.7f, 19.3f, 24.1f, 29.8f, 33.5f,
    38.7f, 43.2f, 49.1f, 55.3f, 61.7f, 68.4f, 76.2f, 85.0f
};

// Right channel - offset by 2-5ms for stereo decorrelation
const float EarlyReflections::tapTimesR[NUM_TAPS] = {
    5.2f,  9.3f,  13.8f, 17.1f, 22.0f, 26.4f, 31.5f, 36.2f,
    41.0f, 46.8f, 52.3f, 58.1f, 64.5f, 71.9f, 79.0f, 87.5f
};

// Base gains with alternating polarity (wall reflections)
const float EarlyReflections::tapGainsBase[NUM_TAPS] = {
    0.85f, -0.72f, 0.65f, -0.58f, 0.52f, -0.46f, 0.41f, -0.37f,
    0.33f, -0.29f, 0.26f, -0.23f, 0.20f, -0.17f, 0.15f, -0.13f
};

// ============================================================
// ERDelayLine
// ============================================================

void EarlyReflections::ERDelayLine::prepare(int maxSamples)
{
    buffer.assign(static_cast<size_t>(maxSamples), 0.0f);
    writePos = 0;
}

void EarlyReflections::ERDelayLine::write(float sample)
{
    buffer[static_cast<size_t>(writePos)] = sample;
    writePos = (writePos + 1) % static_cast<int>(buffer.size());
}

float EarlyReflections::ERDelayLine::read(int delaySamples) const
{
    int bufSize = static_cast<int>(buffer.size());
    int readPos = (writePos - delaySamples + bufSize) % bufSize;
    return buffer[static_cast<size_t>(readPos)];
}

void EarlyReflections::ERDelayLine::clear()
{
    std::fill(buffer.begin(), buffer.end(), 0.0f);
    writePos = 0;
}

// ============================================================
// AllpassDiffuser
// ============================================================

void EarlyReflections::AllpassDiffuser::prepare(int maxSamples)
{
    buffer.assign(static_cast<size_t>(maxSamples), 0.0f);
    writePos = 0;
}

float EarlyReflections::AllpassDiffuser::process(float input)
{
    int bufSize = static_cast<int>(buffer.size());
    int readPos = (writePos - delaySamples + bufSize) % bufSize;
    float delayed = buffer[static_cast<size_t>(readPos)];

    float output = delayed - coeff * input;
    buffer[static_cast<size_t>(writePos)] = input + coeff * delayed;
    writePos = (writePos + 1) % bufSize;
    return output;
}

void EarlyReflections::AllpassDiffuser::clear()
{
    std::fill(buffer.begin(), buffer.end(), 0.0f);
    writePos = 0;
}

// ============================================================
// EarlyReflections
// ============================================================

EarlyReflections::EarlyReflections() {}

void EarlyReflections::prepare(double sampleRate, int /*samplesPerBlock*/)
{
    currentSampleRate = sampleRate;

    // Max delay for ER: 200ms
    int maxDelay = static_cast<int>(sampleRate * 0.2) + 16;
    delayLineL.prepare(maxDelay);
    delayLineR.prepare(maxDelay);

    // Allpass diffusers per channel (short delays for smearing)
    float rateRatio = static_cast<float>(sampleRate / 44100.0);

    // Left diffusers: 1.7ms and 3.1ms
    int diffDelaysL[2] = { static_cast<int>(75 * rateRatio), static_cast<int>(137 * rateRatio) };
    for (int i = 0; i < 2; ++i)
    {
        diffusersL[i].prepare(diffDelaysL[i] + 4);
        diffusersL[i].delaySamples = diffDelaysL[i];
        diffusersL[i].coeff = 0.5f;
    }

    // Right diffusers: 2.1ms and 3.7ms (different from L for stereo)
    int diffDelaysR[2] = { static_cast<int>(93 * rateRatio), static_cast<int>(163 * rateRatio) };
    for (int i = 0; i < 2; ++i)
    {
        diffusersR[i].prepare(diffDelaysR[i] + 4);
        diffusersR[i].delaySamples = diffDelaysR[i];
        diffusersR[i].coeff = 0.5f;
    }

    updateTaps();
}

void EarlyReflections::process(juce::AudioBuffer<float>& buffer)
{
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();

    if (numChannels < 1) return;

    auto* dataL = buffer.getWritePointer(0);
    auto* dataR = numChannels > 1 ? buffer.getWritePointer(1) : nullptr;

    for (int n = 0; n < numSamples; ++n)
    {
        // Diffuse input before writing to ER delay line
        float inL = dataL[n];
        for (auto& d : diffusersL)
            inL = d.process(inL);
        delayLineL.write(inL);

        // Sum taps for left channel
        float erL = 0.0f;
        for (int t = 0; t < NUM_TAPS; ++t)
            erL += delayLineL.read(tapDelayL[t]) * tapGainL[t];

        // Replace output: original + ER
        dataL[n] += erL;

        if (dataR != nullptr)
        {
            float inR = dataR[n];
            for (auto& d : diffusersR)
                inR = d.process(inR);
            delayLineR.write(inR);

            float erR = 0.0f;
            for (int t = 0; t < NUM_TAPS; ++t)
                erR += delayLineR.read(tapDelayR[t]) * tapGainR[t];

            dataR[n] += erR;
        }
    }
}

void EarlyReflections::reset()
{
    delayLineL.clear();
    delayLineR.clear();
    for (auto& d : diffusersL) d.clear();
    for (auto& d : diffusersR) d.clear();
}

void EarlyReflections::setLevel(float newLevel)
{
    level = juce::jlimit(0.0f, 1.0f, newLevel);
    updateTaps();
}

void EarlyReflections::setDecay(float newDecay)
{
    decay = juce::jlimit(0.0f, 1.0f, newDecay);
    updateTaps();
}

void EarlyReflections::setSize(float newSize)
{
    size = juce::jlimit(0.0f, 1.0f, newSize);
    updateTaps();
}

void EarlyReflections::updateTaps()
{
    float sizeScale = 0.3f + size * 1.2f; // 0.3x to 1.5x
    float msToSamples = static_cast<float>(currentSampleRate) / 1000.0f;

    for (int i = 0; i < NUM_TAPS; ++i)
    {
        tapDelayL[i] = juce::jmax(1, static_cast<int>(tapTimesL[i] * sizeScale * msToSamples));
        tapDelayR[i] = juce::jmax(1, static_cast<int>(tapTimesR[i] * sizeScale * msToSamples));

        // Decay-dependent gain: later taps attenuate more with higher decay
        float timeNorm = static_cast<float>(i) / static_cast<float>(NUM_TAPS - 1);
        float decayFactor = std::pow(1.0f - decay * 0.6f, timeNorm * 3.0f);

        tapGainL[i] = tapGainsBase[i] * decayFactor * level;
        tapGainR[i] = tapGainsBase[i] * decayFactor * level;
    }
}
