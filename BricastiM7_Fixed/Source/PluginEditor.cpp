#include "PluginEditor.h"
#include "UI/M7LookAndFeel.h"

BricastiM7AudioProcessorEditor::BricastiM7AudioProcessorEditor (BricastiM7AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Set look and feel
    setLookAndFeel(new M7LookAndFeel());
    
    // Setup sliders
    setupSlider(decayLowSlider, decayLowLabel, "decay_low", "Decay Low");
    setupSlider(decayMidSlider, decayMidLabel, "decay_mid", "Decay Mid");
    setupSlider(decayHighSlider, decayHighLabel, "decay_high", "Decay High");
    setupSlider(preDelaySlider, preDelayLabel, "predelay", "Pre-Delay");
    setupSlider(dampingLowSlider, dampingLowLabel, "damping_low", "Damp Low");
    setupSlider(dampingHighSlider, dampingHighLabel, "damping_high", "Damp High");
    setupSlider(modulationRateSlider, modulationRateLabel, "mod_rate", "Mod Rate");
    setupSlider(modulationDepthSlider, modulationDepthLabel, "mod_depth", "Mod Depth");
    setupSlider(earlyLevelSlider, earlyLevelLabel, "early_level", "Early Level");
    setupSlider(earlyDecaySlider, earlyDecayLabel, "early_decay", "Early Decay");
    setupSlider(sizeSlider, sizeLabel, "size", "Size");
    setupSlider(diffusionSlider, diffusionLabel, "diffusion", "Diffusion");
    setupSlider(lowShelfSlider, lowShelfLabel, "low_shelf", "Low Shelf");
    setupSlider(highShelfSlider, highShelfLabel, "high_shelf", "High Shelf");
    setupSlider(midGainSlider, midGainLabel, "mid_gain", "Mid Gain");
    setupSlider(midFreqSlider, midFreqLabel, "mid_freq", "Mid Freq");
    setupSlider(mixSlider, mixLabel, "mix", "Mix");
    
    // Freeze button
    freezeButton.setButtonText("FREEZE");
    addAndMakeVisible(freezeButton);
    freezeAttachment = std::make_unique<ButtonAttachment>(
        audioProcessor.getValueTreeState(), "freeze", freezeButton
    );
    
    freezeLabel.setText("Freeze", juce::dontSendNotification);
    freezeLabel.attachToComponent(&freezeButton, false);
    addAndMakeVisible(freezeLabel);
    
    // Algorithm combo
    algorithmCombo.addItem("Hall 1", 1);
    algorithmCombo.addItem("Hall 2", 2);
    algorithmCombo.addItem("Hall 3", 3);
    algorithmCombo.addItem("Hall 4", 4);
    algorithmCombo.addItem("Hall 5", 5);
    algorithmCombo.addItem("Hall 6", 6);
    algorithmCombo.addItem("Hall 7", 7);
    algorithmCombo.addItem("Plate 1", 8);
    algorithmCombo.addItem("Plate 2", 9);
    algorithmCombo.addItem("Plate 3", 10);
    algorithmCombo.addItem("Plate 4", 11);
    algorithmCombo.addItem("Plate 5", 12);
    algorithmCombo.addItem("Room 1", 13);
    algorithmCombo.addItem("Room 2", 14);
    algorithmCombo.addItem("Room 3", 15);
    algorithmCombo.addItem("Room 4", 16);
    algorithmCombo.addItem("Chamber 1", 17);
    algorithmCombo.addItem("Chamber 2", 18);
    algorithmCombo.addItem("Chamber 3", 19);
    
    addAndMakeVisible(algorithmCombo);
    algorithmAttachment = std::make_unique<ComboBoxAttachment>(
        audioProcessor.getValueTreeState(), "algorithm", algorithmCombo
    );
    
    algorithmLabel.setText("Algorithm", juce::dontSendNotification);
    algorithmLabel.attachToComponent(&algorithmCombo, false);
    addAndMakeVisible(algorithmLabel);
    
    // Preset combo
    for (int i = 0; i < 30; ++i)
        presetCombo.addItem("Preset " + juce::String(i + 1), i + 1);
    
    addAndMakeVisible(presetCombo);
    presetCombo.onChange = [this]()
    {
        audioProcessor.setCurrentProgram(presetCombo.getSelectedId() - 1);
    };
    
    presetLabel.setText("Preset", juce::dontSendNotification);
    presetLabel.attachToComponent(&presetCombo, false);
    addAndMakeVisible(presetLabel);
    
    setSize (900, 600);
}

BricastiM7AudioProcessorEditor::~BricastiM7AudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void BricastiM7AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xFF1A1A1A));
    
    g.setColour (juce::Colour (0xFF00FF00));
    g.setFont (20.0f);
    g.drawText ("BRICASTI M7", getLocalBounds().removeFromTop(50), 
                juce::Justification::centred);
}

void BricastiM7AudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto topArea = area.removeFromTop(50);
    presetCombo.setBounds(topArea.removeFromRight(150).reduced(5));
    
    area.removeFromTop(20);
    
    // First row: Decay controls
    auto row1 = area.removeFromTop(100);
    decayLowSlider.setBounds(row1.removeFromLeft(80).reduced(5));
    decayMidSlider.setBounds(row1.removeFromLeft(80).reduced(5));
    decayHighSlider.setBounds(row1.removeFromLeft(80).reduced(5));
    preDelaySlider.setBounds(row1.removeFromLeft(80).reduced(5));
    
    // Second row: Damping and modulation
    auto row2 = area.removeFromTop(100);
    dampingLowSlider.setBounds(row2.removeFromLeft(80).reduced(5));
    dampingHighSlider.setBounds(row2.removeFromLeft(80).reduced(5));
    modulationRateSlider.setBounds(row2.removeFromLeft(80).reduced(5));
    modulationDepthSlider.setBounds(row2.removeFromLeft(80).reduced(5));
    
    // Third row: Early reflections and size
    auto row3 = area.removeFromTop(100);
    earlyLevelSlider.setBounds(row3.removeFromLeft(80).reduced(5));
    earlyDecaySlider.setBounds(row3.removeFromLeft(80).reduced(5));
    sizeSlider.setBounds(row3.removeFromLeft(80).reduced(5));
    diffusionSlider.setBounds(row3.removeFromLeft(80).reduced(5));
    
    // Fourth row: EQ
    auto row4 = area.removeFromTop(100);
    lowShelfSlider.setBounds(row4.removeFromLeft(80).reduced(5));
    highShelfSlider.setBounds(row4.removeFromLeft(80).reduced(5));
    midGainSlider.setBounds(row4.removeFromLeft(80).reduced(5));
    midFreqSlider.setBounds(row4.removeFromLeft(80).reduced(5));
    
    // Bottom row: Mix and controls
    auto bottom = area.removeFromTop(80);
    mixSlider.setBounds(bottom.removeFromLeft(100).reduced(5));
    freezeButton.setBounds(bottom.removeFromLeft(100).reduced(5));
    algorithmCombo.setBounds(bottom.removeFromLeft(200).reduced(5));
}

void BricastiM7AudioProcessorEditor::setupSlider(juce::Slider& slider, juce::Label& label,
                                                 const juce::String& paramId, const juce::String& name)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(slider);
    
    label.setText(name, juce::dontSendNotification);
    label.attachToComponent(&slider, false);
    addAndMakeVisible(label);
    
    sliderAttachments.push_back(std::make_unique<SliderAttachment>(
        audioProcessor.getValueTreeState(), paramId, slider
    ));
}