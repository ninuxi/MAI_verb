#include "PluginEditor.h"

RiverberiM7AudioProcessorEditor::RiverberiM7AudioProcessorEditor(RiverberiM7AudioProcessor& p)
    : juce::AudioProcessorEditor(&p), audioProcessor(p)
{
    // Set editor size - wider for better visibility
    setSize(1200, 500);
    setLookAndFeel(&customLookAndFeel);

    // ============ TITLE ============
    titleLabel.setText("RIVERBERO CLONE M7", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    titleLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF00d9ff));
    titleLabel.setFont(juce::Font(32.0f, juce::Font::bold));
    addAndMakeVisible(&titleLabel);

    // ============ DECAY (Reverb Time) ============
    decayLabel.setText("DECAY", juce::dontSendNotification);
    decayLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFcccccc));
    decayLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    decayLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(&decayLabel);
    
    setupSlider(decaySlider, "Decay", 0.5f, 10.0f, 3.0f);
    decaySlider.setSliderStyle(juce::Slider::Rotary);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);
    addAndMakeVisible(&decaySlider);

    sliderAttachments.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.getValueTreeState(), ParameterController::DECAY_ID, decaySlider)
    );

    // ============ PRE-DELAY ============
    predelayLabel.setText("PRE-DELAY (ms)", juce::dontSendNotification);
    predelayLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFcccccc));
    predelayLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    predelayLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(&predelayLabel);
    
    setupSlider(predelaySlider, "Pre-Delay", 0.0f, 500.0f, 0.0f);
    predelaySlider.setSliderStyle(juce::Slider::LinearHorizontal);
    predelaySlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 18);
    addAndMakeVisible(&predelaySlider);

    sliderAttachments.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.getValueTreeState(), ParameterController::PREDELAY_ID, predelaySlider)
    );

    // ============ DAMPING ============
    dampingLabel.setText("DAMPING", juce::dontSendNotification);
    dampingLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFcccccc));
    dampingLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    dampingLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(&dampingLabel);
    
    setupSlider(dampingSlider, "Damping", 0.0f, 1.0f, 0.5f);
    dampingSlider.setSliderStyle(juce::Slider::Rotary);
    dampingSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);
    addAndMakeVisible(&dampingSlider);

    sliderAttachments.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.getValueTreeState(), ParameterController::DAMPING_ID, dampingSlider)
    );

    // ============ STEREO WIDTH ============
    stereoWidthLabel.setText("STEREO WIDTH", juce::dontSendNotification);
    stereoWidthLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFcccccc));
    stereoWidthLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    stereoWidthLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(&stereoWidthLabel);
    
    setupSlider(stereoWidthSlider, "Stereo Width", 0.0f, 1.0f, 0.7f);
    stereoWidthSlider.setSliderStyle(juce::Slider::Rotary);
    stereoWidthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);
    addAndMakeVisible(&stereoWidthSlider);

    sliderAttachments.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.getValueTreeState(), ParameterController::STEREO_WIDTH_ID, stereoWidthSlider)
    );

    // ============ EARLY REFLECTIONS ============
    earlyReflectionsLabel.setText("EARLY REFL", juce::dontSendNotification);
    earlyReflectionsLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFcccccc));
    earlyReflectionsLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    earlyReflectionsLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(&earlyReflectionsLabel);
    
    setupSlider(earlyReflectionsSlider, "Early Reflections", 0.0f, 1.0f, 0.5f);
    earlyReflectionsSlider.setSliderStyle(juce::Slider::Rotary);
    earlyReflectionsSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);
    addAndMakeVisible(&earlyReflectionsSlider);

    sliderAttachments.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.getValueTreeState(), ParameterController::EARLY_REFL_ID, earlyReflectionsSlider)
    );

    // ============ WET MIX ============
    mixLabel.setText("WET MIX", juce::dontSendNotification);
    mixLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFcccccc));
    mixLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    mixLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(&mixLabel);
    
    setupSlider(mixSlider, "Mix", 0.0f, 1.0f, 0.5f);
    mixSlider.setSliderStyle(juce::Slider::LinearVertical);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);
    addAndMakeVisible(&mixSlider);

    sliderAttachments.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.getValueTreeState(), ParameterController::MIX_ID, mixSlider)
    );

    // ============ SIZE ============
    sizeLabel.setText("SIZE", juce::dontSendNotification);
    sizeLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFcccccc));
    sizeLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    sizeLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(&sizeLabel);
    
    setupSlider(sizeSlider, "Size", 0.0f, 1.0f, 0.7f);
    sizeSlider.setSliderStyle(juce::Slider::Rotary);
    sizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);
    addAndMakeVisible(&sizeSlider);

    sliderAttachments.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.getValueTreeState(), ParameterController::SIZE_ID, sizeSlider)
    );

    // ============ DIFFUSION ============
    diffusionLabel.setText("DIFFUSION", juce::dontSendNotification);
    diffusionLabel.setColour(juce::Label::textColourId, juce::Colour(0xFFcccccc));
    diffusionLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    diffusionLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(&diffusionLabel);
    
    setupSlider(diffusionSlider, "Diffusion", 0.0f, 1.0f, 0.8f);
    diffusionSlider.setSliderStyle(juce::Slider::Rotary);
    diffusionSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 18);
    addAndMakeVisible(&diffusionSlider);

    sliderAttachments.push_back(
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            audioProcessor.getValueTreeState(), ParameterController::DIFFUSION_ID, diffusionSlider)
    );

    // ============ FREEZE ============
    freezeButton.setButtonText("FREEZE");
    freezeButton.setColour(juce::ToggleButton::tickColourId, juce::Colour(0xFF00d9ff));
    freezeButton.setColour(juce::ToggleButton::textColourId, juce::Colour(0xFFcccccc));
    addAndMakeVisible(&freezeButton);

    freezeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        audioProcessor.getValueTreeState(), ParameterController::FREEZE_ID, freezeButton
    );

    // ============ PRESET SELECTOR ============
    presetSelector.addItem("Cathedral", 1);
    presetSelector.addItem("Hall (Large)", 2);
    presetSelector.addItem("Hall (Medium)", 3);
    presetSelector.addItem("Plate (Bright)", 4);
    presetSelector.addItem("Room (Small)", 5);
    presetSelector.setSelectedItemIndex(0);
    presetSelector.setColour(juce::ComboBox::backgroundColourId, juce::Colour(0xFF2a2a2a));
    presetSelector.setColour(juce::ComboBox::textColourId, juce::Colour(0xFF00d9ff));
    addAndMakeVisible(&presetSelector);

    // ============ STATUS LABELS ============
    versionLabel.setText("v0.0.0", juce::dontSendNotification);
    versionLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF666666));
    versionLabel.setFont(juce::Font(9.0f));
    addAndMakeVisible(&versionLabel);

    cpuLoadLabel.setText("CPU: --", juce::dontSendNotification);
    cpuLoadLabel.setColour(juce::Label::textColourId, juce::Colour(0xFF00d9ff));
    cpuLoadLabel.setFont(juce::Font(10.0f));
    addAndMakeVisible(&cpuLoadLabel);
}

RiverberiM7AudioProcessorEditor::~RiverberiM7AudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void RiverberiM7AudioProcessorEditor::paint(juce::Graphics& g)
{
    // Dark background
    g.fillAll(juce::Colour(0xFF0d0d0d));

    // Accent line at top
    g.setColour(juce::Colour(0xFF00d9ff));
    g.fillRect(0, 0, getWidth(), 2);

    // Version badge
    g.setColour(juce::Colour(0xFF1a1a1a));
    g.fillRoundedRectangle(getWidth() - 80, getHeight() - 25, 70, 20, 3.0f);
}

void RiverberiM7AudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    const int padding = 10;
    const int knobSize = 70;
    const int labelHeight = 16;

    // Title area (top)
    auto titleArea = bounds.removeFromTop(50);
    titleLabel.setBounds(titleArea.reduced(padding));

    // Main parameter area
    auto mainArea = bounds.removeFromTop(250);
    
    // Row 1: Decay, Pre-Delay slider, Damping
    auto row1 = mainArea.removeFromTop(130);
    
    int x = padding;
    // Decay
    decayLabel.setBounds(x, row1.getY() + 5, 80, labelHeight);
    decaySlider.setBounds(x, row1.getY() + labelHeight + 5, knobSize, knobSize);
    x += knobSize + 20;

    // Pre-Delay (horizontal slider)
    predelayLabel.setBounds(x, row1.getY() + 5, 120, labelHeight);
    predelaySlider.setBounds(x, row1.getY() + labelHeight + 5, 200, 35);
    x += 220;

    // Damping
    dampingLabel.setBounds(x, row1.getY() + 5, 80, labelHeight);
    dampingSlider.setBounds(x, row1.getY() + labelHeight + 5, knobSize, knobSize);
    x += knobSize + 20;

    // Stereo Width
    stereoWidthLabel.setBounds(x, row1.getY() + 5, 100, labelHeight);
    stereoWidthSlider.setBounds(x, row1.getY() + labelHeight + 5, knobSize, knobSize);
    x += knobSize + 20;

    // Early Reflections
    earlyReflectionsLabel.setBounds(x, row1.getY() + 5, 100, labelHeight);
    earlyReflectionsSlider.setBounds(x, row1.getY() + labelHeight + 5, knobSize, knobSize);

    // Row 2: Size, Diffusion, Freeze, Wet Mix (vertical)
    auto row2 = mainArea.removeFromTop(130);
    
    x = padding;
    // Size
    sizeLabel.setBounds(x, row2.getY() + 5, 80, labelHeight);
    sizeSlider.setBounds(x, row2.getY() + labelHeight + 5, knobSize, knobSize);
    x += knobSize + 20;

    // Diffusion
    diffusionLabel.setBounds(x, row2.getY() + 5, 80, labelHeight);
    diffusionSlider.setBounds(x, row2.getY() + labelHeight + 5, knobSize, knobSize);
    x += knobSize + 20;

    // Freeze button (large)
    freezeButton.setBounds(x, row2.getY() + 20, 100, 80);
    x += 120;

    // Wet Mix (vertical slider)
    mixLabel.setBounds(x, row2.getY() + 5, 80, labelHeight);
    mixSlider.setBounds(x, row2.getY() + labelHeight + 5, 60, knobSize);

    // Bottom section: Presets and status
    auto bottomArea = bounds.removeFromTop(80);
    
    // Preset selector
    presetSelector.setBounds(padding, bottomArea.getY() + 20, 150, 30);

    // Status labels
    cpuLoadLabel.setBounds(padding + 160, bottomArea.getY() + 20, 120, 30);
    versionLabel.setBounds(getWidth() - 75, getHeight() - 22, 65, 20);
}

void RiverberiM7AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // Parameter updates are handled automatically by SliderAttachment
}

void RiverberiM7AudioProcessorEditor::setupSlider(juce::Slider& slider, const juce::String& name,
                                                   float minVal, float maxVal, float defaultVal)
{
    slider.setRange(minVal, maxVal, 0.01f);
    slider.setValue(defaultVal);
    slider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFF00d9ff));
    slider.setColour(juce::Slider::trackColourId, juce::Colour(0xFF333333));
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xFF00d9ff));
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(0xFF555555));
    slider.addListener(this);
}
