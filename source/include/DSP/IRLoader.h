#pragma once

#include <JuceHeader.h>
#include <vector>

/**
 * IRLoader: Handles impulse response file loading and processing
 * Supports WAV, AIFF and other formats via JUCE audio format readers
 */
class IRLoader
{
public:
    IRLoader() = default;
    ~IRLoader() = default;

    /**
     * Load impulse response from file
     * @param file Path to audio file
     * @param targetSampleRate Optional sample rate conversion
     * @return Audio buffer with IR data
     */
    static juce::AudioBuffer<float> loadIRFromFile(const juce::File& file,
                                                    double targetSampleRate = 0.0);

    /**
     * Load IR from input stream
     * @param stream Input stream containing audio data
     * @return Audio buffer with IR data
     */
    static juce::AudioBuffer<float> loadIRFromStream(juce::InputStream& stream,
                                                      double targetSampleRate = 0.0);

    /**
     * Generate synthetic IR for testing
     * @param durationMs Duration in milliseconds
     * @param decayFactor Exponential decay factor (0.0-1.0)
     * @param sampleRate Sample rate in Hz
     * @return Generated IR buffer
     */
    static juce::AudioBuffer<float> generateSyntheticIR(float durationMs,
                                                         float decayFactor,
                                                         double sampleRate);

    /**
     * Normalize IR to prevent clipping
     * @param buffer Buffer to normalize
     */
    static void normalizeIR(juce::AudioBuffer<float>& buffer);

    /**
     * Apply crossfade between IRs
     * @param from Starting IR
     * @param to Ending IR
     * @param crossfadeDurationMs Crossfade duration
     * @param position Current position (0.0-1.0)
     * @return Crossfaded IR
     */
    static juce::AudioBuffer<float> crossfadeIRs(const juce::AudioBuffer<float>& from,
                                                   const juce::AudioBuffer<float>& to,
                                                   float crossfadeDurationMs,
                                                   float position);

private:
    // Supported audio formats registration
    static void registerAudioFormats();
};
