#pragma once

#include <JuceHeader.h>
#include "DSP/ConvolutionEngine.h"
#include "DSP/ParameterController.h"

class RiverberiM7AudioProcessor : public juce::AudioProcessor
{
public:
    RiverberiM7AudioProcessor();
    ~RiverberiM7AudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override;

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }

    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    // Audio processing capabilities
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    // Parameter access
    juce::AudioProcessorValueTreeState& getValueTreeState() { return parameters; }

    // Convolution engine access
    ConvolutionEngine& getConvolutionEngine() { return convolutionEngine; }
    ParameterController& getParameterController() { return parameterController; }

private:
    // APVTS for parameter management
    juce::AudioProcessorValueTreeState parameters;

    // DSP components
    ConvolutionEngine convolutionEngine;
    ParameterController parameterController;

    // Processing state
    double currentSampleRate = 44100.0;
    int currentBlockSize = 512;

    // Dry/wet mix processing
    juce::dsp::DryWetMixer<float> dryWetMixer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RiverberiM7AudioProcessor)
};
