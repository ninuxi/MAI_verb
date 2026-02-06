#include "DSP/ConvolutionEngine.h"
#include "DSP/IRLoader.h"
#include <algorithm>
#include <cmath>

ConvolutionEngine::ConvolutionEngine()
{
    comb1Buffer.resize(1116, 0.0f);
    comb2Buffer.resize(1188, 0.0f);
    comb3Buffer.resize(1277, 0.0f);
    comb4Buffer.resize(1356, 0.0f);
    
    allpass1Buffer.resize(556, 0.0f);
    allpass2Buffer.resize(441, 0.0f);
    allpass3Buffer.resize(341, 0.0f);
    allpass4Buffer.resize(225, 0.0f);

    preDelayBuffer.setSize(2, 48000, true, true, true);
}

ConvolutionEngine::~ConvolutionEngine() {}

void ConvolutionEngine::prepare(double inSampleRate, int inBlockSize, int maxIRSize)
{
    sampleRate = inSampleRate;
    blockSize = inBlockSize;

    float scaleFactor = static_cast<float>(inSampleRate) / 44100.0f;
    
    comb1Buffer.resize(static_cast<size_t>(1116 * scaleFactor), 0.0f);
    comb2Buffer.resize(static_cast<size_t>(1188 * scaleFactor), 0.0f);
    comb3Buffer.resize(static_cast<size_t>(1277 * scaleFactor), 0.0f);
    comb4Buffer.resize(static_cast<size_t>(1356 * scaleFactor), 0.0f);

    allpass1Buffer.resize(static_cast<size_t>(556 * scaleFactor), 0.0f);
    allpass2Buffer.resize(static_cast<size_t>(441 * scaleFactor), 0.0f);
    allpass3Buffer.resize(static_cast<size_t>(341 * scaleFactor), 0.0f);
    allpass4Buffer.resize(static_cast<size_t>(225 * scaleFactor), 0.0f);

    preDelayBuffer.setSize(2, static_cast<int>(inSampleRate * 1.0), true, true, true);
}

void ConvolutionEngine::reset()
{
    std::fill(comb1Buffer.begin(), comb1Buffer.end(), 0.0f);
    std::fill(comb2Buffer.begin(), comb2Buffer.end(), 0.0f);
    std::fill(comb3Buffer.begin(), comb3Buffer.end(), 0.0f);
    std::fill(comb4Buffer.begin(), comb4Buffer.end(), 0.0f);
    
    std::fill(allpass1Buffer.begin(), allpass1Buffer.end(), 0.0f);
    std::fill(allpass2Buffer.begin(), allpass2Buffer.end(), 0.0f);
    std::fill(allpass3Buffer.begin(), allpass3Buffer.end(), 0.0f);
    std::fill(allpass4Buffer.begin(), allpass4Buffer.end(), 0.0f);

    comb1Index = comb2Index = comb3Index = comb4Index = 0;
    allpass1Index = allpass2Index = allpass3Index = allpass4Index = 0;
    preDelayWritePos = 0;
}

bool ConvolutionEngine::loadImpulseResponse(const juce::File& irFile)
{
    return true;
}

void ConvolutionEngine::setImpulseResponse(const juce::AudioBuffer<float>& irBuffer, int channel)
{
    juce::ignoreUnused(irBuffer, channel);
}

float ConvolutionEngine::processCombFilter(float input, std::vector<float>& buffer,
                                           size_t& writeIndex, float feedback, float damping)
{
    float bufferOut = buffer[writeIndex];
    feedbackFilter = (bufferOut * (1.0f - damping)) + (feedbackFilter * damping);
    buffer[writeIndex] = input + (feedbackFilter * feedback);
    writeIndex = (writeIndex + 1) % buffer.size();
    return bufferOut;
}

float ConvolutionEngine::processAllpassFilter(float input, std::vector<float>& buffer, size_t& writeIndex)
{
    const float allpassFeedback = 0.5f;
    float bufferOut = buffer[writeIndex];
    float output = -input + bufferOut;
    buffer[writeIndex] = input + (bufferOut * allpassFeedback);
    writeIndex = (writeIndex + 1) % buffer.size();
    return output;
}

void ConvolutionEngine::processBlock(juce::AudioBuffer<float>& buffer)
{
    int numSamples = buffer.getNumSamples();
    auto numChannels = buffer.getNumChannels();
    int preDelaySize = preDelayBuffer.getNumSamples();

    for (int ch = 0; ch < numChannels; ++ch)
    {
        auto* channelData = buffer.getWritePointer(ch);

        for (int n = 0; n < numSamples; ++n)
        {
            float input = channelData[n];

            if (preDelayMs > 0.01f)
            {
                int delayIndex = preDelayWritePos;
                float delayedSample = preDelayBuffer.getSample(ch, delayIndex);
                preDelayBuffer.setSample(ch, delayIndex, input);
                preDelayWritePos = (preDelayWritePos + 1) % preDelaySize;
                input = delayedSample;
            }

            float combOut1 = processCombFilter(input, comb1Buffer, comb1Index, feedback, damping);
            float combOut2 = processCombFilter(input, comb2Buffer, comb2Index, feedback, damping);
            float combOut3 = processCombFilter(input, comb3Buffer, comb3Index, feedback, damping);
            float combOut4 = processCombFilter(input, comb4Buffer, comb4Index, feedback, damping);

            float combMix = (combOut1 + combOut2 + combOut3 + combOut4) * 0.25f;

            float allpassOut = processAllpassFilter(combMix, allpass1Buffer, allpass1Index);
            allpassOut = processAllpassFilter(allpassOut, allpass2Buffer, allpass2Index);
            allpassOut = processAllpassFilter(allpassOut, allpass3Buffer, allpass3Index);
            allpassOut = processAllpassFilter(allpassOut, allpass4Buffer, allpass4Index);

            channelData[n] = (allpassOut * wetDryMix) + (channelData[n] * (1.0f - wetDryMix));
            channelData[n] = std::tanh(channelData[n]);
        }
    }
}
