#include "FDN8x8.h"

// Hadamard 8x8 matrix (normalized by 1/sqrt(8))
const float FDN8x8::hadamard[NUM_DELAYS][NUM_DELAYS] = {
    { NORM,  NORM,  NORM,  NORM,  NORM,  NORM,  NORM,  NORM},
    { NORM, -NORM,  NORM, -NORM,  NORM, -NORM,  NORM, -NORM},
    { NORM,  NORM, -NORM, -NORM,  NORM,  NORM, -NORM, -NORM},
    { NORM, -NORM, -NORM,  NORM,  NORM, -NORM, -NORM,  NORM},
    { NORM,  NORM,  NORM,  NORM, -NORM, -NORM, -NORM, -NORM},
    { NORM, -NORM,  NORM, -NORM, -NORM,  NORM, -NORM,  NORM},
    { NORM,  NORM, -NORM, -NORM, -NORM, -NORM,  NORM,  NORM},
    { NORM, -NORM, -NORM,  NORM, -NORM,  NORM,  NORM, -NORM}
};

// ============================================================
// ModulatedDelayLine
// ============================================================

void FDN8x8::ModulatedDelayLine::prepare(int maxSamples)
{
    buffer.assign(static_cast<size_t>(maxSamples), 0.0f);
    writePos = 0;
}

void FDN8x8::ModulatedDelayLine::write(float sample)
{
    buffer[static_cast<size_t>(writePos)] = sample;
    writePos = (writePos + 1) % static_cast<int>(buffer.size());
}

float FDN8x8::ModulatedDelayLine::readModulated()
{
    // Advance LFO
    lfoPhase += lfoPhaseIncrement;
    if (lfoPhase >= juce::MathConstants<float>::twoPi)
        lfoPhase -= juce::MathConstants<float>::twoPi;

    float modOffset = std::sin(lfoPhase) * lfoDepth;

    // Fractional read position
    float readPosF = static_cast<float>(writePos) - baseDelaySamples + modOffset;
    int bufSize = static_cast<int>(buffer.size());

    while (readPosF < 0.0f)
        readPosF += static_cast<float>(bufSize);

    // Linear interpolation
    int idx0 = static_cast<int>(readPosF) % bufSize;
    int idx1 = (idx0 + 1) % bufSize;
    float frac = readPosF - std::floor(readPosF);

    return buffer[static_cast<size_t>(idx0)] * (1.0f - frac)
         + buffer[static_cast<size_t>(idx1)] * frac;
}

void FDN8x8::ModulatedDelayLine::clear()
{
    std::fill(buffer.begin(), buffer.end(), 0.0f);
    writePos = 0;
}

// ============================================================
// FeedbackFilter (one-pole LP for damping)
// ============================================================

float FDN8x8::FeedbackFilter::process(float sample)
{
    // One-pole lowpass for high-frequency damping (most musical, like air absorption)
    // y[n] = x[n] * (1 - c) + y[n-1] * c
    lpState = sample * (1.0f - lpCoeff) + lpState * lpCoeff;
    return lpState;
}

void FDN8x8::FeedbackFilter::setFrequencies(float lpFreq, float hpFreq, double sampleRate)
{
    float sr = static_cast<float>(sampleRate);
    lpFreq = juce::jlimit(200.0f, sr * 0.49f, lpFreq);
    hpFreq = juce::jlimit(20.0f, 2000.0f, hpFreq);

    // One-pole coefficient from cutoff frequency
    // c = exp(-2*pi*f/sr) -> higher c = lower cutoff (more damping)
    lpCoeff = std::exp(-juce::MathConstants<float>::twoPi * lpFreq / sr);
    hpCoeff = std::exp(-juce::MathConstants<float>::twoPi * hpFreq / sr);
}

void FDN8x8::FeedbackFilter::reset()
{
    lpState = 0.0f;
    hpState = 0.0f;
}

// ============================================================
// AllpassFilter (input diffusion)
// ============================================================

void FDN8x8::AllpassFilter::prepare(int maxSamples)
{
    buffer.assign(static_cast<size_t>(maxSamples), 0.0f);
    writePos = 0;
}

float FDN8x8::AllpassFilter::process(float input)
{
    int bufSize = static_cast<int>(buffer.size());
    int readPos = (writePos - delaySamples + bufSize) % bufSize;
    float delayed = buffer[static_cast<size_t>(readPos)];

    float output = delayed - coefficient * input;
    buffer[static_cast<size_t>(writePos)] = input + coefficient * delayed;
    writePos = (writePos + 1) % bufSize;
    return output;
}

void FDN8x8::AllpassFilter::clear()
{
    std::fill(buffer.begin(), buffer.end(), 0.0f);
    writePos = 0;
}

// ============================================================
// FDN8x8 main class
// ============================================================

FDN8x8::FDN8x8() {}

void FDN8x8::prepare(double sampleRate, int /*samplesPerBlock*/)
{
    currentSampleRate = sampleRate;

    int maxDelay = static_cast<int>(sampleRate * 2.0) + 16;

    for (int i = 0; i < NUM_DELAYS; ++i)
    {
        delays[i].prepare(maxDelay);
        feedbackFilters[i].reset();
    }

    // Input diffusers
    float rateRatio = static_cast<float>(sampleRate / 44100.0);
    for (int i = 0; i < 4; ++i)
    {
        int scaledDelay = static_cast<int>(diffuserDelays[i] * rateRatio);
        inputDiffusers[i].prepare(scaledDelay + 4);
        inputDiffusers[i].delaySamples = scaledDelay;
    }

    updateDelayTimes();
    updateDampingFilters();
    updateModulation();

    // Set initial LFO phases for decorrelation
    for (int i = 0; i < NUM_DELAYS; ++i)
        delays[i].lfoPhase = lfoBasePhases[i];
}

void FDN8x8::process(float inputL, float inputR, float& outputL, float& outputR)
{
    // Step 1: Input diffusion
    float monoIn = (inputL + inputR) * 0.5f;
    float diffCoeff = 0.3f + diffusionAmount * 0.4f;

    for (int i = 0; i < 4; ++i)
    {
        inputDiffusers[i].coefficient = diffCoeff;
        monoIn = inputDiffusers[i].process(monoIn);
    }

    // Step 2: Read ALL delay outputs FIRST
    float delayOutputs[NUM_DELAYS];
    for (int i = 0; i < NUM_DELAYS; ++i)
        delayOutputs[i] = delays[i].readModulated();

    // Step 3: Apply feedback damping
    float filtered[NUM_DELAYS];
    for (int i = 0; i < NUM_DELAYS; ++i)
        filtered[i] = feedbackFilters[i].process(delayOutputs[i]);

    // Step 4: Apply RT60-based feedback gains
    for (int i = 0; i < NUM_DELAYS; ++i)
        filtered[i] *= feedbackGains[i];

    // Step 5: Hadamard matrix mixing with diffusion control
    float mixed[NUM_DELAYS];
    for (int i = 0; i < NUM_DELAYS; ++i)
    {
        float matrixSum = 0.0f;
        for (int j = 0; j < NUM_DELAYS; ++j)
            matrixSum += hadamard[i][j] * filtered[j];

        mixed[i] = (1.0f - diffusionAmount) * filtered[i] + diffusionAmount * matrixSum;
    }

    // Step 6: Add input and write to delay lines
    float inputGain = 0.25f;
    for (int i = 0; i < NUM_DELAYS; ++i)
    {
        float newSample = mixed[i] + monoIn * inputGain;
        newSample = std::tanh(newSample); // soft clip for safety

        if (!freezeMode)
            delays[i].write(newSample);
    }

    // Step 7: Decorrelated stereo output
    outputL = 0.0f;
    outputR = 0.0f;

    for (int i = 0; i < NUM_DELAYS; ++i)
    {
        if (i % 2 == 0)
        {
            outputL += delayOutputs[i];
            outputR -= delayOutputs[i] * 0.25f;
        }
        else
        {
            outputR += delayOutputs[i];
            outputL -= delayOutputs[i] * 0.25f;
        }
    }

    outputL *= 0.2f;
    outputR *= 0.2f;
}

void FDN8x8::reset()
{
    for (int i = 0; i < NUM_DELAYS; ++i)
    {
        delays[i].clear();
        feedbackFilters[i].reset();
        feedbackGains[i] = 0.0f;
    }
    for (auto& ap : inputDiffusers)
        ap.clear();
}

void FDN8x8::setDecayTimes(float low, float mid, float high)
{
    rt60Low = juce::jlimit(0.1f, 30.0f, low);
    rt60Mid = juce::jlimit(0.1f, 30.0f, mid);
    rt60High = juce::jlimit(0.1f, 30.0f, high);
    updateFeedbackGains();
}

void FDN8x8::setDamping(float lowDampParam, float highDampParam)
{
    dampLow = juce::jlimit(0.0f, 1.0f, lowDampParam);
    dampHigh = juce::jlimit(0.0f, 1.0f, highDampParam);
    updateDampingFilters();
}

void FDN8x8::setSize(float size)
{
    roomSize = juce::jlimit(0.0f, 1.0f, size);
    updateDelayTimes();
}

void FDN8x8::setDiffusion(float diffusion)
{
    diffusionAmount = juce::jlimit(0.0f, 1.0f, diffusion);
}

void FDN8x8::setModulation(float rate, float depth)
{
    modRate = juce::jlimit(0.1f, 10.0f, rate);
    modDepth = juce::jlimit(0.0f, 1.0f, depth);
    updateModulation();
}

void FDN8x8::setFreeze(bool freeze)
{
    freezeMode = freeze;
    updateFeedbackGains();
}

void FDN8x8::updateDelayTimes()
{
    float sizeScale = 0.3f + roomSize * 1.2f;
    float rateRatio = static_cast<float>(currentSampleRate / 44100.0);

    for (int i = 0; i < NUM_DELAYS; ++i)
        delays[i].baseDelaySamples = baseDelaysAt44100[i] * rateRatio * sizeScale;

    updateFeedbackGains();
}

void FDN8x8::updateFeedbackGains()
{
    float sr = static_cast<float>(currentSampleRate);

    for (int i = 0; i < NUM_DELAYS; ++i)
    {
        float D = delays[i].baseDelaySamples;

        if (freezeMode)
        {
            feedbackGains[i] = 1.0f;
        }
        else
        {
            float rt60 = juce::jmax(0.1f, rt60Mid);
            feedbackGains[i] = std::pow(10.0f, -3.0f * D / (rt60 * sr));
        }
    }
}

void FDN8x8::updateDampingFilters()
{
    float lpFreq = 1000.0f + (1.0f - dampHigh) * 14000.0f;
    float hpFreq = 20.0f + dampLow * 480.0f;

    for (int i = 0; i < NUM_DELAYS; ++i)
        feedbackFilters[i].setFrequencies(lpFreq, hpFreq, currentSampleRate);
}

void FDN8x8::updateModulation()
{
    float sr = static_cast<float>(currentSampleRate);
    float twoPi = juce::MathConstants<float>::twoPi;

    for (int i = 0; i < NUM_DELAYS; ++i)
    {
        float rateHz = lfoBaseRates[i] * modRate;
        float depthSamples = 0.5f + modDepth * 3.0f;

        delays[i].lfoDepth = depthSamples;
        delays[i].lfoPhaseIncrement = twoPi * rateHz / sr;
    }
}
