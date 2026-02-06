#pragma once

#include <JuceHeader.h>
#include <vector>

/**
 * SampleRateConfig: Manages multi-sample rate support
 * Handles resampling and buffer management for 44.1k - 192k sample rates
 */
class SampleRateConfig
{
public:
    // Supported sample rates
    static constexpr std::array<double, 6> SUPPORTED_RATES = {
        44100.0,
        48000.0,
        88200.0,
        96000.0,
        176400.0,
        192000.0
    };

    /**
     * Check if sample rate is supported
     */
    static bool isSupported(double sampleRate)
    {
        for (auto rate : SUPPORTED_RATES)
        {
            if (std::abs(sampleRate - rate) < 1.0)
                return true;
        }
        return false;
    }

    /**
     * Get nearest supported sample rate
     */
    static double getNearestSupported(double sampleRate)
    {
        double nearest = SUPPORTED_RATES[0];
        double minDiff = std::abs(sampleRate - nearest);

        for (auto rate : SUPPORTED_RATES)
        {
            double diff = std::abs(sampleRate - rate);
            if (diff < minDiff)
            {
                minDiff = diff;
                nearest = rate;
            }
        }

        return nearest;
    }

    /**
     * Get resampling factor for IR at different sample rate
     */
    static double getResamplingFactor(double fromRate, double toRate)
    {
        return toRate / fromRate;
    }

    /**
     * Calculate optimal FFT size for IR at given sample rate
     */
    static int getOptimalFFTSize(double sampleRate, float maxIRLengthMs = 5000.0f)
    {
        int maxSamples = static_cast<int>(maxIRLengthMs * sampleRate / 1000.0f);

        // Find next power of 2
        int fftSize = 1;
        while (fftSize < maxSamples)
            fftSize *= 2;

        return fftSize;
    }

    /**
     * Get buffer size recommendations for sample rate
     */
    static int getRecommendedBlockSize(double sampleRate)
    {
        // Smaller buffers at higher sample rates to maintain latency
        if (sampleRate > 176000.0)
            return 512;
        if (sampleRate > 96000.0)
            return 256;
        return 128;
    }

    /**
     * Calculate actual latency at given sample rate
     */
    static float getLatencyMs(double sampleRate, int blockSize)
    {
        return (blockSize / sampleRate) * 1000.0f;
    }
};

/**
 * ResamplingUtility: Helper for IR resampling
 */
class ResamplingUtility
{
public:
    /**
     * Resample audio buffer using linear interpolation
     * @param source Source buffer
     * @param factor Resampling factor (>1 = upsample, <1 = downsample)
     * @return Resampled buffer
     */
    static juce::AudioBuffer<float> resampleLinear(const juce::AudioBuffer<float>& source,
                                                     double factor)
    {
        if (std::abs(factor - 1.0) < 0.001)
            return source; // No resampling needed

        int newSize = static_cast<int>(source.getNumSamples() * factor);
        juce::AudioBuffer<float> result(source.getNumChannels(), newSize);

        for (int ch = 0; ch < source.getNumChannels(); ++ch)
        {
            auto* srcData = source.getReadPointer(ch);
            auto* dstData = result.getWritePointer(ch);

            for (int n = 0; n < newSize; ++n)
            {
                double srcPos = n / factor;
                int srcIdx = static_cast<int>(srcPos);
                double frac = srcPos - srcIdx;

                if (srcIdx + 1 < source.getNumSamples())
                {
                    // Linear interpolation
                    dstData[n] = srcData[srcIdx] * (1.0f - frac) +
                                srcData[srcIdx + 1] * frac;
                }
                else if (srcIdx < source.getNumSamples())
                {
                    dstData[n] = srcData[srcIdx];
                }
                else
                {
                    dstData[n] = 0.0f;
                }
            }
        }

        return result;
    }

    /**
     * Apply anti-aliasing filter before downsampling
     */
    static juce::AudioBuffer<float> applyAntiAliasingFilter(const juce::AudioBuffer<float>& buffer,
                                                              double sampleRate)
    {
        // Nyquist frequency
        double nyquist = sampleRate / 2.0;

        // Simple 4-pole butterworth filter at Nyquist/2
        juce::AudioBuffer<float> filtered = buffer;

        // Basic 1-pole filter implementation
        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            auto* data = filtered.getWritePointer(ch);
            float coeff = 0.1f; // Filter coefficient

            for (int i = 1; i < buffer.getNumSamples(); ++i)
            {
                data[i] = data[i-1] * (1.0f - coeff) + data[i] * coeff;
            }
        }

        return filtered;
    }
};
