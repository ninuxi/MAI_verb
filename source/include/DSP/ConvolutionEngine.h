#pragma once

#include <JuceHeader.h>
#include <vector>

/**
 * ConvolutionEngine: Schroeder Reverberator Algorithm
 * Based on classic Schroeder reverb design with:
 * - 4 parallel comb filters (feedback + damping)
 * - 4 series allpass filters (diffusion)
 * - Pre-delay support
 * - Wet/dry mix control
 */
class ConvolutionEngine
{
public:
    ConvolutionEngine();
    ~ConvolutionEngine();

    /**
     * Prepare reverb engine for processing
     */
    void prepare(double sampleRate, int blockSize, int maxIRSize = 131072);

    /**
     * Reset processing state
     */
    void reset();

    /**
     * Load impulse response from file (optional)
     */
    bool loadImpulseResponse(const juce::File& irFile);

    /**
     * Set impulse response from buffer (optional)
     */
    void setImpulseResponse(const juce::AudioBuffer<float>& irBuffer, int channel = 0);

    /**
     * Process audio block with reverb
     */
    void processBlock(juce::AudioBuffer<float>& buffer);

    /**
     * Set wet/dry mix (0.0 = dry, 1.0 = wet)
     */
    void setWetDryMix(float mix) { wetDryMix = mix; }

    /**
     * Set decay/feedback amount (0.5 to 0.9)
     */
    void setDecayScaling(float factor) { feedback = factor * 0.9f; }

    /**
     * Set pre-delay in milliseconds
     */
    void setPreDelay(float ms) { preDelayMs = ms; }

    /**
     * Set damping (0.0 = no damping, 1.0 = full damping)
     */
    void setDamping(float damp) { damping = damp; }

    /**
     * Check if impulse response is loaded
     */
    bool hasImpulseResponse() const { return !irData.empty(); }

private:
    // Process helper functions
    float processCombFilter(float input, std::vector<float>& buffer,
                          size_t& writeIndex, float feedback, float damping);
    float processAllpassFilter(float input, std::vector<float>& buffer, size_t& writeIndex);

    // Schroeder reverb buffers
    std::vector<float> comb1Buffer, comb2Buffer, comb3Buffer, comb4Buffer;
    std::vector<float> allpass1Buffer, allpass2Buffer, allpass3Buffer, allpass4Buffer;
    
    size_t comb1Index = 0, comb2Index = 0, comb3Index = 0, comb4Index = 0;
    size_t allpass1Index = 0, allpass2Index = 0, allpass3Index = 0, allpass4Index = 0;

    // Optional IR data for convolution
    std::vector<float> irData;

    // Parameters
    double sampleRate = 44100.0;
    int blockSize = 512;
    float wetDryMix = 0.5f;
    float feedback = 0.84f;  // Typical feedback for reverb tail
    float damping = 0.5f;     // Controls high-frequency damping
    float preDelayMs = 0.0f;
    float feedbackFilter = 0.0f;

    // Pre-delay buffer
    juce::AudioBuffer<float> preDelayBuffer;
    int preDelayWritePos = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ConvolutionEngine)
};
