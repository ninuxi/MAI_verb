#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_dsp/juce_dsp.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "DSP/M7ReverbEngine.h"
#include "Presets/M7FactoryPresets.h"

class BricastiM7AudioProcessor  : public juce::AudioProcessor
{
public:
    BricastiM7AudioProcessor();
    ~BricastiM7AudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "Mainenti Reverb"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 10.0; }

    int getNumPrograms() override { return M7FactoryPresets::getNumPresets(); }
    int getCurrentProgram() override { return currentPreset; }
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override
    {
        return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo()
            && layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo();
    }

    juce::AudioProcessorValueTreeState& getValueTreeState() { return apvts; }

private:
    M7ReverbEngine reverbEngine;

    juce::AudioProcessorValueTreeState apvts;

    std::atomic<float>* decayLowParam = nullptr;
    std::atomic<float>* decayMidParam = nullptr;
    std::atomic<float>* decayHighParam = nullptr;
    std::atomic<float>* preDelayParam = nullptr;
    std::atomic<float>* dampingLowParam = nullptr;
    std::atomic<float>* dampingHighParam = nullptr;
    std::atomic<float>* modulationRateParam = nullptr;
    std::atomic<float>* modulationDepthParam = nullptr;
    std::atomic<float>* earlyLevelParam = nullptr;
    std::atomic<float>* earlyDecayParam = nullptr;
    std::atomic<float>* sizeParam = nullptr;
    std::atomic<float>* diffusionParam = nullptr;
    std::atomic<float>* lowShelfParam = nullptr;
    std::atomic<float>* highShelfParam = nullptr;
    std::atomic<float>* midGainParam = nullptr;
    std::atomic<float>* midFreqParam = nullptr;
    std::atomic<float>* mixParam = nullptr;
    std::atomic<float>* freezeParam = nullptr;
    std::atomic<float>* algorithmParam = nullptr;

    int currentPreset = 0;

    void updateEngineParameters();
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BricastiM7AudioProcessor)
};
