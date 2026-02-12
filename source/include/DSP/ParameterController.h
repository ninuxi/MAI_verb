#pragma once

#include <JuceHeader.h>

/**
 * ParameterController: Manages all plugin parameters
 * Provides APVTS setup and parameter access for M7-inspired reverb
 */
class ParameterController
{
public:
    // Parameter IDs
    static constexpr auto DECAY_ID = "decay";
    static constexpr auto PREDELAY_ID = "predelay";
    static constexpr auto DAMPING_ID = "damping";
    static constexpr auto STEREO_WIDTH_ID = "stereoWidth";
    static constexpr auto EARLY_REFL_ID = "earlyReflections";
    static constexpr auto MIX_ID = "mix";
    static constexpr auto SIZE_ID = "size";
    static constexpr auto FREEZE_ID = "freeze";
    static constexpr auto DIFFUSION_ID = "diffusion";

    ParameterController();
    ~ParameterController() = default;

    /**
     * Create and return parameter layout for APVTS
     */
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    /**
     * Get parameter by ID
     * @param parameterId Parameter ID string
     * @return Parameter pointer
     */
    juce::AudioProcessorParameter* getParameter(const juce::String& parameterId);

    /**
     * Get parameter value (normalized 0.0-1.0)
     */
    float getParameterValue(const juce::String& parameterId) const;

    /**
     * Get parameter value in actual units
     */
    float getParameterValueInUnits(const juce::String& parameterId) const;

    /**
     * Initialize with APVTS
     */
    void initialize(juce::AudioProcessorValueTreeState* vts);

    // Parameter access through helper methods
    float getDecay() const;
    float getPreDelay() const;
    float getDamping() const;
    float getStereoWidth() const;
    float getEarlyReflections() const;
    float getMix() const;
    float getSize() const;
    bool getFreeze() const;
    float getDiffusion() const;

private:
    juce::AudioProcessorValueTreeState* valueTreeState = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterController)
};
