#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>
#include "FDN8x8.h"
#include "EarlyReflections.h"
#include "M7EQ.h"

/**
 * M7ReverbEngine: Main reverb engine coordinator.
 *
 * Signal flow:
 * Input -> PreDelay -> [split]
 *   (a) EarlyReflections * earlyLevel
 *   (b) FDN8x8 (with input diffusion and modulation)
 *   -> [ER + FDN] -> EQ -> wet signal
 * Output = dry * (1-mix) + wet * mix
 */
class M7ReverbEngine
{
public:
    M7ReverbEngine();
    ~M7ReverbEngine() = default;

    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();

    // Parameters
    void setDecay(float low, float mid, float high);
    void setPreDelay(float ms);
    void setDamping(float low, float high);
    void setModulation(float rate, float depth);
    void setEarlyReflections(float level, float decay);
    void setSize(float size);
    void setDiffusion(float diffusion);
    void setEQ(float lowShelf, float highShelf, float midGain, float midFreq);
    void setMix(float mix);
    void setFreeze(bool freeze);

    // Algorithms
    enum Algorithm {
        HALL_1 = 0, HALL_2, HALL_3, HALL_4, HALL_5, HALL_6, HALL_7,
        PLATE_1, PLATE_2, PLATE_3, PLATE_4, PLATE_5,
        ROOM_1, ROOM_2, ROOM_3, ROOM_4,
        CHAMBER_1, CHAMBER_2, CHAMBER_3,
        NUM_ALGORITHMS
    };

    void setAlgorithm(Algorithm algorithm);

private:
    FDN8x8 fdn;
    EarlyReflections earlyReflections;
    M7EQ eqProcessor;

    // Smoothed parameters
    juce::SmoothedValue<float> smoothMix;
    juce::SmoothedValue<float> smoothEarlyLevel;

    // Pre-delay
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> preDelayLine{48000};

    float decayLow = 3.0f, decayMid = 2.0f, decayHigh = 1.5f;
    float preDelayMs = 0.0f;
    float dampingLow = 0.5f, dampingHigh = 0.5f;
    float modulationRate = 1.0f, modulationDepth = 0.3f;
    float earlyLevel = 0.5f, earlyDecay = 0.5f;
    float roomSize = 0.7f;
    float diffusionAmount = 0.8f;
    float mix = 0.5f;
    bool freezeActive = false;

    juce::AudioBuffer<float> dryBuffer, wetBuffer, erBuffer;

    double currentSampleRate = 44100.0;
    int currentBlockSize = 512;

    void updateParameters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(M7ReverbEngine)
};
