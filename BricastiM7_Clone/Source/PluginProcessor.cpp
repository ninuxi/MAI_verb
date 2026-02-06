#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DSP/M7Parameters.h"

BricastiM7AudioProcessor::BricastiM7AudioProcessor()
    : AudioProcessor (BusesProperties()
                     .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                     .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "Parameters", createParameterLayout())
{
    // Connect parameters via getRawParameterValue (thread-safe atomic access)
    decayLowParam = apvts.getRawParameterValue (M7Parameters::DECAY_LOW_ID);
    decayMidParam = apvts.getRawParameterValue (M7Parameters::DECAY_MID_ID);
    decayHighParam = apvts.getRawParameterValue (M7Parameters::DECAY_HIGH_ID);
    preDelayParam = apvts.getRawParameterValue (M7Parameters::PRE_DELAY_ID);
    dampingLowParam = apvts.getRawParameterValue (M7Parameters::DAMPING_LOW_ID);
    dampingHighParam = apvts.getRawParameterValue (M7Parameters::DAMPING_HIGH_ID);
    modulationRateParam = apvts.getRawParameterValue (M7Parameters::MOD_RATE_ID);
    modulationDepthParam = apvts.getRawParameterValue (M7Parameters::MOD_DEPTH_ID);
    earlyLevelParam = apvts.getRawParameterValue (M7Parameters::EARLY_LEVEL_ID);
    earlyDecayParam = apvts.getRawParameterValue (M7Parameters::EARLY_DECAY_ID);
    sizeParam = apvts.getRawParameterValue (M7Parameters::SIZE_ID);
    diffusionParam = apvts.getRawParameterValue (M7Parameters::DIFFUSION_ID);
    lowShelfParam = apvts.getRawParameterValue (M7Parameters::LOW_SHELF_ID);
    highShelfParam = apvts.getRawParameterValue (M7Parameters::HIGH_SHELF_ID);
    midGainParam = apvts.getRawParameterValue (M7Parameters::MID_GAIN_ID);
    midFreqParam = apvts.getRawParameterValue (M7Parameters::MID_FREQ_ID);
    mixParam = apvts.getRawParameterValue (M7Parameters::MIX_ID);
    freezeParam = apvts.getRawParameterValue (M7Parameters::FREEZE_ID);
    algorithmParam = apvts.getRawParameterValue (M7Parameters::ALGORITHM_ID);

    // Load first preset
    setCurrentProgram(0);
}

BricastiM7AudioProcessor::~BricastiM7AudioProcessor() {}

void BricastiM7AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    reverbEngine.prepare(sampleRate, samplesPerBlock);
    updateEngineParameters();
}

void BricastiM7AudioProcessor::releaseResources() {}

void BricastiM7AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    updateEngineParameters();
    reverbEngine.process(buffer);
}

juce::AudioProcessorEditor* BricastiM7AudioProcessor::createEditor()
{
    return new BricastiM7AudioProcessorEditor (*this);
}

void BricastiM7AudioProcessor::setCurrentProgram (int index)
{
    int numPresets = M7FactoryPresets::getNumPresets();
    if (numPresets == 0) return;

    currentPreset = index % numPresets;
    auto preset = M7FactoryPresets::getPreset(currentPreset);

    for (const auto& paramPair : preset.parameters)
    {
        if (auto* param = apvts.getParameter(paramPair.first))
        {
            // Convert raw value to normalized 0-1 range before setting
            float normalizedValue = param->convertTo0to1(paramPair.second);
            param->setValueNotifyingHost(normalizedValue);
        }
    }
}

const juce::String BricastiM7AudioProcessor::getProgramName (int index)
{
    int numPresets = M7FactoryPresets::getNumPresets();
    if (numPresets == 0) return "Default";
    return M7FactoryPresets::getPreset(index % numPresets).name;
}

void BricastiM7AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused(index, newName);
}

void BricastiM7AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void BricastiM7AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState != nullptr && xmlState->hasTagName (apvts.state.getType()))
        apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

void BricastiM7AudioProcessor::updateEngineParameters()
{
    reverbEngine.setDecay (*decayLowParam, *decayMidParam, *decayHighParam);
    reverbEngine.setPreDelay (*preDelayParam);
    reverbEngine.setDamping (*dampingLowParam, *dampingHighParam);
    reverbEngine.setModulation (*modulationRateParam, *modulationDepthParam);
    reverbEngine.setEarlyReflections (*earlyLevelParam, *earlyDecayParam);
    reverbEngine.setSize (*sizeParam);
    reverbEngine.setDiffusion (*diffusionParam);
    reverbEngine.setEQ (*lowShelfParam, *highShelfParam, *midGainParam, *midFreqParam);
    reverbEngine.setMix (*mixParam);
    reverbEngine.setFreeze (*freezeParam > 0.5f);

    int algo = static_cast<int>(*algorithmParam);
    if (algo >= 0 && algo < M7ReverbEngine::NUM_ALGORITHMS)
        reverbEngine.setAlgorithm (static_cast<M7ReverbEngine::Algorithm>(algo));
}

juce::AudioProcessorValueTreeState::ParameterLayout BricastiM7AudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::DECAY_LOW_ID, "Decay Low",
        juce::NormalisableRange<float> (0.1f, 20.0f, 0.1f), 3.0f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::DECAY_MID_ID, "Decay Mid",
        juce::NormalisableRange<float> (0.1f, 20.0f, 0.1f), 2.0f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::DECAY_HIGH_ID, "Decay High",
        juce::NormalisableRange<float> (0.1f, 20.0f, 0.1f), 1.5f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::PRE_DELAY_ID, "Pre-Delay",
        juce::NormalisableRange<float> (0.0f, 500.0f, 1.0f), 0.0f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::DAMPING_LOW_ID, "Damping Low",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f), 0.5f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::DAMPING_HIGH_ID, "Damping High",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f), 0.5f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::MOD_RATE_ID, "Mod Rate",
        juce::NormalisableRange<float> (0.1f, 10.0f, 0.1f), 1.0f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::MOD_DEPTH_ID, "Mod Depth",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f), 0.3f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::EARLY_LEVEL_ID, "Early Level",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f), 0.5f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::EARLY_DECAY_ID, "Early Decay",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f), 0.5f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::SIZE_ID, "Size",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f), 0.7f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::DIFFUSION_ID, "Diffusion",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f), 0.8f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::LOW_SHELF_ID, "Low Shelf",
        juce::NormalisableRange<float> (-12.0f, 12.0f, 0.1f), 0.0f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::HIGH_SHELF_ID, "High Shelf",
        juce::NormalisableRange<float> (-12.0f, 12.0f, 0.1f), 0.0f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::MID_GAIN_ID, "Mid Gain",
        juce::NormalisableRange<float> (-12.0f, 12.0f, 0.1f), 0.0f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::MID_FREQ_ID, "Mid Freq",
        juce::NormalisableRange<float> (100.0f, 5000.0f, 1.0f), 1000.0f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        M7Parameters::MIX_ID, "Mix",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f), 0.5f));

    params.push_back (std::make_unique<juce::AudioParameterBool> (
        M7Parameters::FREEZE_ID, "Freeze", false));

    juce::StringArray algorithms = {
        "Hall 1", "Hall 2", "Hall 3", "Hall 4", "Hall 5", "Hall 6", "Hall 7",
        "Plate 1", "Plate 2", "Plate 3", "Plate 4", "Plate 5",
        "Room 1", "Room 2", "Room 3", "Room 4",
        "Chamber 1", "Chamber 2", "Chamber 3"
    };

    params.push_back (std::make_unique<juce::AudioParameterChoice> (
        M7Parameters::ALGORITHM_ID, "Algorithm", algorithms, 0));

    return { params.begin(), params.end() };
}

//==============================================================================
juce::AudioProcessor* createPluginFilter()
{
    return new BricastiM7AudioProcessor();
}
