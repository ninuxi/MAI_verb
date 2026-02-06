#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_dsp/juce_dsp.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "PluginProcessor.h"
#include "UI/M7LookAndFeel.h"

class BricastiM7AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BricastiM7AudioProcessorEditor (BricastiM7AudioProcessor&);
    ~BricastiM7AudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BricastiM7AudioProcessor& audioProcessor;

    // LookAndFeel as member (RAII - no memory leak)
    M7LookAndFeel lookAndFeel;

    // Sliders
    juce::Slider decayLowSlider, decayMidSlider, decayHighSlider;
    juce::Slider preDelaySlider;
    juce::Slider dampingLowSlider, dampingHighSlider;
    juce::Slider modulationRateSlider, modulationDepthSlider;
    juce::Slider earlyLevelSlider, earlyDecaySlider;
    juce::Slider sizeSlider, diffusionSlider;
    juce::Slider lowShelfSlider, highShelfSlider;
    juce::Slider midGainSlider, midFreqSlider;
    juce::Slider mixSlider;
    juce::ToggleButton freezeButton;
    juce::ComboBox algorithmCombo;
    juce::ComboBox presetCombo;

    // Labels
    juce::Label decayLowLabel, decayMidLabel, decayHighLabel;
    juce::Label preDelayLabel;
    juce::Label dampingLowLabel, dampingHighLabel;
    juce::Label modulationRateLabel, modulationDepthLabel;
    juce::Label earlyLevelLabel, earlyDecayLabel;
    juce::Label sizeLabel, diffusionLabel;
    juce::Label lowShelfLabel, highShelfLabel;
    juce::Label midGainLabel, midFreqLabel;
    juce::Label mixLabel;
    juce::Label freezeLabel;
    juce::Label algorithmLabel;
    juce::Label presetLabel;

    // Attachments
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    std::vector<std::unique_ptr<SliderAttachment>> sliderAttachments;
    std::unique_ptr<ButtonAttachment> freezeAttachment;
    std::unique_ptr<ComboBoxAttachment> algorithmAttachment;

    void setupSlider(juce::Slider& slider, juce::Label& label,
                    const juce::String& paramId, const juce::String& name);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BricastiM7AudioProcessorEditor)
};
