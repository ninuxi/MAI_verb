#include "DSP/ParameterController.h"

ParameterController::ParameterController()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout ParameterController::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Decay: 0.5s to 10s
    params.push_back(
        std::make_unique<juce::AudioParameterFloat>(
            DECAY_ID, "Decay",
            juce::NormalisableRange<float>(0.5f, 10.0f, 0.1f),
            3.0f,
            "s",
            juce::AudioProcessorParameter::genericParameter,
            [](float value, int) { return juce::String(value, 2) + " s"; },
            [](const juce::String& text) { return text.dropLastCharacters(2).getFloatValue(); }
        )
    );

    // Pre-delay: 0ms to 1000ms
    params.push_back(
        std::make_unique<juce::AudioParameterFloat>(
            PREDELAY_ID, "Pre-Delay",
            juce::NormalisableRange<float>(0.0f, 1000.0f, 1.0f),
            0.0f,
            "ms",
            juce::AudioProcessorParameter::genericParameter,
            [](float value, int) { return juce::String(static_cast<int>(value)) + " ms"; },
            [](const juce::String& text) { return text.dropLastCharacters(3).getFloatValue(); }
        )
    );

    // Damping: 0.0 to 1.0
    params.push_back(
        std::make_unique<juce::AudioParameterFloat>(
            DAMPING_ID, "Damping",
            juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
            0.5f,
            "",
            juce::AudioProcessorParameter::genericParameter,
            [](float value, int) { return juce::String(value * 100.0f, 1) + "%"; },
            [](const juce::String& text) { return text.dropLastCharacters(1).getFloatValue() / 100.0f; }
        )
    );

    // Stereo Width: 0.0 to 1.0
    params.push_back(
        std::make_unique<juce::AudioParameterFloat>(
            STEREO_WIDTH_ID, "Stereo Width",
            juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
            0.7f,
            "",
            juce::AudioProcessorParameter::genericParameter,
            [](float value, int) { return juce::String(value * 100.0f, 1) + "%"; },
            [](const juce::String& text) { return text.dropLastCharacters(1).getFloatValue() / 100.0f; }
        )
    );

    // Early Reflections: 0.0 to 1.0
    params.push_back(
        std::make_unique<juce::AudioParameterFloat>(
            EARLY_REFL_ID, "Early Reflections",
            juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
            0.5f,
            "",
            juce::AudioProcessorParameter::genericParameter,
            [](float value, int) { return juce::String(value * 100.0f, 1) + "%"; },
            [](const juce::String& text) { return text.dropLastCharacters(1).getFloatValue() / 100.0f; }
        )
    );

    // Mix/Wet: 0.0 to 1.0
    params.push_back(
        std::make_unique<juce::AudioParameterFloat>(
            MIX_ID, "Mix",
            juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
            0.5f,
            "",
            juce::AudioProcessorParameter::genericParameter,
            [](float value, int) { return juce::String(value * 100.0f, 1) + "%"; },
            [](const juce::String& text) { return text.dropLastCharacters(1).getFloatValue() / 100.0f; }
        )
    );

    // Size: 0.0 to 1.0 (room size scaling)
    params.push_back(
        std::make_unique<juce::AudioParameterFloat>(
            SIZE_ID, "Size",
            juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
            0.7f,
            "",
            juce::AudioProcessorParameter::genericParameter,
            [](float value, int) { return juce::String(value * 100.0f, 1) + "%"; },
            [](const juce::String& text) { return text.dropLastCharacters(1).getFloatValue() / 100.0f; }
        )
    );

    // Freeze: boolean
    params.push_back(
        std::make_unique<juce::AudioParameterBool>(
            FREEZE_ID, "Freeze",
            false,
            "",
            nullptr,
            nullptr
        )
    );

    // Diffusion: 0.0 to 1.0
    params.push_back(
        std::make_unique<juce::AudioParameterFloat>(
            DIFFUSION_ID, "Diffusion",
            juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
            0.8f,
            "",
            juce::AudioProcessorParameter::genericParameter,
            [](float value, int) { return juce::String(value * 100.0f, 1) + "%"; },
            [](const juce::String& text) { return text.dropLastCharacters(1).getFloatValue() / 100.0f; }
        )
    );

    return { params.begin(), params.end() };
}

juce::AudioProcessorParameter* ParameterController::getParameter(const juce::String& parameterId)
{
    if (valueTreeState == nullptr)
        return nullptr;

    return valueTreeState->getParameter(parameterId);
}

float ParameterController::getParameterValue(const juce::String& parameterId) const
{
    if (valueTreeState == nullptr)
        return 0.0f;

    auto* param = valueTreeState->getParameter(parameterId);

    if (param == nullptr)
        return 0.0f;

    return param->getValue();
}

float ParameterController::getParameterValueInUnits(const juce::String& parameterId) const
{
    if (valueTreeState == nullptr)
        return 0.0f;

    auto* param = dynamic_cast<juce::RangedAudioParameter*>(
        valueTreeState->getParameter(parameterId));

    if (param == nullptr)
        return 0.0f;

    return param->convertFrom0to1(param->getValue());
}

void ParameterController::initialize(juce::AudioProcessorValueTreeState* vts)
{
    valueTreeState = vts;
}

float ParameterController::getDecay() const
{
    return getParameterValueInUnits(DECAY_ID);
}

float ParameterController::getPreDelay() const
{
    return getParameterValueInUnits(PREDELAY_ID);
}

float ParameterController::getDamping() const
{
    return getParameterValueInUnits(DAMPING_ID);
}

float ParameterController::getStereoWidth() const
{
    return getParameterValueInUnits(STEREO_WIDTH_ID);
}

float ParameterController::getEarlyReflections() const
{
    return getParameterValueInUnits(EARLY_REFL_ID);
}

float ParameterController::getMix() const
{
    return getParameterValueInUnits(MIX_ID);
}

float ParameterController::getSize() const
{
    return getParameterValueInUnits(SIZE_ID);
}

bool ParameterController::getFreeze() const
{
    auto* param = dynamic_cast<juce::AudioParameterBool*>(
        valueTreeState->getParameter(FREEZE_ID));

    if (param == nullptr)
        return false;

    return param->get();
}

float ParameterController::getDiffusion() const
{
    return getParameterValueInUnits(DIFFUSION_ID);
}
