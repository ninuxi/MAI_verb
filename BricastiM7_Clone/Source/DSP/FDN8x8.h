#pragma once
#include <juce_dsp/juce_dsp.h>
#include <array>
#include <cmath>
#include <vector>

/**
 * FDN8x8: 8-channel Feedback Delay Network for high-quality algorithmic reverb.
 *
 * Features:
 * - 8 modulated delay lines with prime-length delays (20-51ms range)
 * - Hadamard 8x8 mixing matrix (energy-preserving)
 * - RT60-based per-delay feedback gain calculation
 * - Multi-band damping via one-pole filters in feedback loop
 * - Input diffusion via 4 nested allpass filters
 * - Delay line modulation to eliminate metallic ringing
 * - Freeze mode (infinite sustain)
 */
class FDN8x8
{
public:
    static constexpr int NUM_DELAYS = 8;

    FDN8x8();
    ~FDN8x8() = default;

    void prepare(double sampleRate, int samplesPerBlock);
    void process(float inputL, float inputR, float& outputL, float& outputR);
    void reset();

    void setDecayTimes(float rt60Low, float rt60Mid, float rt60High);
    void setDamping(float lowDamp, float highDamp);
    void setSize(float size);
    void setDiffusion(float diffusion);
    void setModulation(float rate, float depth);
    void setFreeze(bool freeze);

private:
    // --- Modulated Delay Line ---
    struct ModulatedDelayLine
    {
        std::vector<float> buffer;
        int writePos = 0;
        float baseDelaySamples = 0.0f;

        float lfoPhase = 0.0f;
        float lfoDepth = 0.0f;
        float lfoPhaseIncrement = 0.0f;

        void prepare(int maxSamples);
        void write(float sample);
        float readModulated();
        void clear();
    };

    // --- One-pole feedback filter for damping ---
    struct FeedbackFilter
    {
        float lpState = 0.0f;
        float hpState = 0.0f;
        float lpCoeff = 0.0f;
        float hpCoeff = 0.0f;

        float process(float sample);
        void setFrequencies(float lpFreq, float hpFreq, double sampleRate);
        void reset();
    };

    // --- Allpass filter for input diffusion ---
    struct AllpassFilter
    {
        std::vector<float> buffer;
        int writePos = 0;
        int delaySamples = 0;
        float coefficient = 0.5f;

        void prepare(int maxSamples);
        float process(float input);
        void clear();
    };

    std::array<ModulatedDelayLine, NUM_DELAYS> delays;
    std::array<FeedbackFilter, NUM_DELAYS> feedbackFilters;
    std::array<AllpassFilter, 4> inputDiffusers;
    std::array<float, NUM_DELAYS> feedbackGains = {};

    double currentSampleRate = 44100.0;

    // Parameters
    float rt60Low = 3.0f, rt60Mid = 2.0f, rt60High = 1.5f;
    float roomSize = 0.7f;
    float diffusionAmount = 0.8f;
    float modRate = 0.8f;
    float modDepth = 0.3f;
    float dampLow = 0.5f;
    float dampHigh = 0.5f;
    bool freezeMode = false;

    // Prime delay lengths at 44100 Hz (20-51ms range)
    static constexpr int baseDelaysAt44100[NUM_DELAYS] = {
        887, 1097, 1361, 1559, 1709, 1867, 2053, 2251
    };

    // Hadamard 8x8 normalized matrix
    static constexpr float NORM = 0.3535533905932738f; // 1/sqrt(8)
    static const float hadamard[NUM_DELAYS][NUM_DELAYS];

    // LFO rates for decorrelation
    static constexpr float lfoBaseRates[NUM_DELAYS] = {
        0.31f, 0.37f, 0.43f, 0.53f, 0.61f, 0.71f, 0.79f, 0.89f
    };
    static constexpr float lfoBasePhases[NUM_DELAYS] = {
        0.0f, 0.79f, 1.57f, 2.36f, 3.14f, 3.93f, 4.71f, 5.50f
    };

    // Input diffuser delays (prime, at 44100 Hz)
    static constexpr int diffuserDelays[4] = { 53, 89, 127, 179 };

    void updateDelayTimes();
    void updateFeedbackGains();
    void updateDampingFilters();
    void updateModulation();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FDN8x8)
};
