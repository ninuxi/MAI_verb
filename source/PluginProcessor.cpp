#include "PluginProcessor.h"
#include "PluginEditor.h"

// Constructor
RiverberiM7AudioProcessor::RiverberiM7AudioProcessor()
    : juce::AudioProcessor(
        BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    parameters(*this, nullptr, juce::Identifier("RiverberiM7"),
               ParameterController::createParameterLayout()),
    parameterController()
{
    parameterController.initialize(&parameters);
    dryWetMixer.setWetMixProportion(0.5f);
}

RiverberiM7AudioProcessor::~RiverberiM7AudioProcessor()
{
}

void RiverberiM7AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    currentBlockSize = samplesPerBlock;

    // Prepare DSP modules
    convolutionEngine.prepare(sampleRate, samplesPerBlock);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    dryWetMixer.prepare(spec);
}

void RiverberiM7AudioProcessor::releaseResources()
{
    // Free up any resources
}

void RiverberiM7AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear output channels that don't have input
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Get parameters
    float mix = parameterController.getMix();
    float decay = parameterController.getDecay();
    float damping = parameterController.getDamping();
    float stereoWidth = parameterController.getStereoWidth();
    float preDelay = parameterController.getPreDelay();
    float earlyReflections = parameterController.getEarlyReflections();
    bool freeze = parameterController.getFreeze();
    float diffusion = parameterController.getDiffusion();

    // Apply Schroeder reverb (always active, no need for IR)
    convolutionEngine.setWetDryMix(mix);
    convolutionEngine.setDecayScaling(decay);
    convolutionEngine.setDamping(damping);
    convolutionEngine.setPreDelay(preDelay);
    
    // Process through reverb engine
    convolutionEngine.processBlock(buffer);
    
    if (false)  // Keep for future IR loading feature
    {
        // Placeholder for future IR convolution
    }

    // Limit output to prevent clipping
    auto* channelDataL = buffer.getWritePointer(0);
    auto* channelDataR = buffer.getNumChannels() > 1 ? buffer.getWritePointer(1) : nullptr;

    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        channelDataL[i] = juce::jlimit(-1.0f, 1.0f, channelDataL[i]);
        if (channelDataR != nullptr)
            channelDataR[i] = juce::jlimit(-1.0f, 1.0f, channelDataR[i]);
    }
}

juce::AudioProcessorEditor* RiverberiM7AudioProcessor::createEditor()
{
    return new RiverberiM7AudioProcessorEditor(*this);
}

const juce::String RiverberiM7AudioProcessor::getName() const
{
    return "Riverberi M7";
}

double RiverberiM7AudioProcessor::getTailLengthSeconds() const
{
    // For Schroeder reverb, estimate tail length based on feedback
    // Default is 5 seconds (can be adjusted based on parameters)
    return 5.0;
}

int RiverberiM7AudioProcessor::getNumPrograms()
{
    return 1;
}

int RiverberiM7AudioProcessor::getCurrentProgram()
{
    return 0;
}

void RiverberiM7AudioProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

const juce::String RiverberiM7AudioProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}

void RiverberiM7AudioProcessor::changeProgramName(int index, const juce::String& newName)
{
    juce::ignoreUnused(index, newName);
}

void RiverberiM7AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void RiverberiM7AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

bool RiverberiM7AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // Only support stereo I/O
    if (layouts.getMainOutputChannels() != 2)
        return false;

    if (layouts.getMainInputChannels() != 2)
        return false;

    return true;
}

// Entry point for plugin creation
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RiverberiM7AudioProcessor();
}
