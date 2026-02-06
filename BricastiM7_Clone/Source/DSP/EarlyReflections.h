#pragma once
#include <juce_dsp/juce_dsp.h>
#include <array>
#include <vector>

/**
 * EarlyReflections: 16-tap stereo-decorrelated early reflections processor.
 *
 * Features:
 * - 16 taps with different L/R delay times for stereo imaging
 * - Alternating polarity gains for natural wall-reflection simulation
 * - 2 allpass diffusers per channel for density
 * - Size and decay controls
 */
class EarlyReflections
{
public:
    static constexpr int NUM_TAPS = 16;

    EarlyReflections();
    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();

    void setLevel(float level);
    void setDecay(float decay);
    void setSize(float size);

private:
    struct ERDelayLine
    {
        std::vector<float> buffer;
        int writePos = 0;

        void prepare(int maxSamples);
        void write(float sample);
        float read(int delaySamples) const;
        void clear();
    };

    struct AllpassDiffuser
    {
        std::vector<float> buffer;
        int writePos = 0;
        int delaySamples = 0;
        float coeff = 0.5f;

        void prepare(int maxSamples);
        float process(float input);
        void clear();
    };

    ERDelayLine delayLineL, delayLineR;
    std::array<AllpassDiffuser, 2> diffusersL, diffusersR;

    // Tap times in ms (different for L and R)
    static const float tapTimesL[NUM_TAPS];
    static const float tapTimesR[NUM_TAPS];
    static const float tapGainsBase[NUM_TAPS];

    int tapDelayL[NUM_TAPS] = {};
    int tapDelayR[NUM_TAPS] = {};
    float tapGainL[NUM_TAPS] = {};
    float tapGainR[NUM_TAPS] = {};

    float level = 0.5f;
    float decay = 0.5f;
    float size = 0.7f;
    double currentSampleRate = 44100.0;

    void updateTaps();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EarlyReflections)
};
