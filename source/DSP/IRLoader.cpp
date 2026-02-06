#include "DSP/IRLoader.h"

juce::AudioBuffer<float> IRLoader::loadIRFromFile(const juce::File& file,
                                                   double targetSampleRate)
{
    juce::AudioBuffer<float> resultBuffer;

    if (!file.exists())
        return resultBuffer;

    // Create format manager and reader
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    auto reader = std::unique_ptr<juce::AudioFormatReader>(formatManager.createReaderFor(file));

    if (reader == nullptr)
        return resultBuffer;

    // Read audio data
    int numSamples = static_cast<int>(reader->lengthInSamples);
    int numChannels = reader->numChannels;

    resultBuffer.setSize(numChannels, numSamples, false, true, true);

    reader->read(&resultBuffer, 0, numSamples, 0, true, true);

    // Resample if needed - for now, just use at native sample rate
    if (targetSampleRate > 0.0 && std::abs(reader->sampleRate - targetSampleRate) > 1.0)
    {
        // Note: Full resampling would require juce::LagrangeInterpolator or similar
        // For now, just pass through the data as-is
    }

    // Normalize
    normalizeIR(resultBuffer);

    return resultBuffer;
}

juce::AudioBuffer<float> IRLoader::loadIRFromStream(juce::InputStream& stream,
                                                     double targetSampleRate)
{
    juce::AudioBuffer<float> resultBuffer;
    // Stream-based loading not directly supported in this version
    // Use loadIRFromFile instead with a File object
    return resultBuffer;
}

juce::AudioBuffer<float> IRLoader::generateSyntheticIR(float durationMs,
                                                        float decayFactor,
                                                        double sampleRate)
{
    juce::AudioBuffer<float> resultBuffer;

    int numSamples = static_cast<int>(durationMs * sampleRate / 1000.0f);
    resultBuffer.setSize(1, numSamples, true, true, true);

    auto* data = resultBuffer.getWritePointer(0);

    // Generate exponentially decaying noise
    juce::Random random;

    for (int i = 0; i < numSamples; ++i)
    {
        float decayEnvelope = std::exp(-decayFactor * i / sampleRate);
        data[i] = (random.nextFloat() - 0.5f) * 2.0f * decayEnvelope;
    }

    normalizeIR(resultBuffer);

    return resultBuffer;
}

void IRLoader::normalizeIR(juce::AudioBuffer<float>& buffer)
{
    float maxVal = 0.0f;

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        auto* data = buffer.getReadPointer(ch);

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            maxVal = std::max(maxVal, std::abs(data[i]));
        }
    }

    if (maxVal > 0.0f)
    {
        float normFactor = 0.95f / maxVal;

        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            auto* data = buffer.getWritePointer(ch);
            juce::FloatVectorOperations::multiply(data, normFactor, buffer.getNumSamples());
        }
    }
}

juce::AudioBuffer<float> IRLoader::crossfadeIRs(const juce::AudioBuffer<float>& from,
                                                  const juce::AudioBuffer<float>& to,
                                                  float crossfadeDurationMs,
                                                  float position)
{
    juce::AudioBuffer<float> resultBuffer;

    int maxSize = std::max(from.getNumSamples(), to.getNumSamples());
    resultBuffer.setSize(1, maxSize, true, true, true);

    auto* outData = resultBuffer.getWritePointer(0);
    auto* fromData = from.getReadPointer(0);
    auto* toData = to.getReadPointer(0);

    position = juce::jlimit(0.0f, 1.0f, position);

    for (int i = 0; i < maxSize; ++i)
    {
        float fromSample = i < from.getNumSamples() ? fromData[i] : 0.0f;
        float toSample = i < to.getNumSamples() ? toData[i] : 0.0f;

        outData[i] = fromSample * (1.0f - position) + toSample * position;
    }

    normalizeIR(resultBuffer);

    return resultBuffer;
}

void IRLoader::registerAudioFormats()
{
    // Audio formats are registered in loadIRFromFile
}
