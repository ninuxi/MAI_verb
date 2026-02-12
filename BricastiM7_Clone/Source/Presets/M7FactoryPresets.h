#pragma once
#include <juce_core/juce_core.h>
#include "../DSP/M7Parameters.h"

struct M7Preset
{
    juce::String name;
    std::vector<std::pair<juce::String, float>> parameters;
};

class M7FactoryPresets
{
public:
    static M7Preset getPreset(int index);
    static int getNumPresets() { return static_cast<int>(presets.size()); }

private:
    static const std::vector<M7Preset> presets;
};
