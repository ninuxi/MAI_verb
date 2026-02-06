#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/CustomLookAndFeel.h"

/**
 * RiverberiM7AudioProcessorEditor: Main UI for the plugin
 * Features modern interface with sliders, knobs, and preset management
 */
class RiverberiM7AudioProcessorEditor : public juce::AudioProcessorEditor,
                                         public juce::Slider::Listener
{
public:
    RiverberiM7AudioProcessorEditor(RiverberiM7AudioProcessor&);
    ~RiverberiM7AudioProcessorEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    RiverberiM7AudioProcessor& audioProcessor;

    // Custom look and feel
    CustomLookAndFeel customLookAndFeel;

    // Title and info
    juce::Label titleLabel;
    juce::Label versionLabel;

    // UI Components - Main parameters
    juce::Slider decaySlider;
    juce::Label decayLabel;

    juce::Slider predelaySlider;
    juce::Label predelayLabel;

    juce::Slider dampingSlider;
    juce::Label dampingLabel;

    juce::Slider stereoWidthSlider;
    juce::Label stereoWidthLabel;

    juce::Slider earlyReflectionsSlider;
    juce::Label earlyReflectionsLabel;

    juce::Slider mixSlider;
    juce::Label mixLabel;

    juce::Slider sizeSlider;
    juce::Label sizeLabel;

    juce::Slider diffusionSlider;
    juce::Label diffusionLabel;

    // Toggle buttons
    juce::ToggleButton freezeButton;
    juce::Label freezeLabel;

    // Preset management
    juce::ComboBox presetSelector;
    juce::TextButton loadIRButton;
    juce::TextButton savePresetButton;

    // Status display
    juce::Label cpuLoadLabel;
    juce::Label irInfoLabel;

    // Attachment objects
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> freezeAttachment;

    // Helper methods
    void setupSlider(juce::Slider& slider, const juce::String& name,
                     float minVal, float maxVal, float defaultVal);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RiverberiM7AudioProcessorEditor)
};
