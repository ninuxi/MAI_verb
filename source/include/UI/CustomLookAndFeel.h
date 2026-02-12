#pragma once

#include <JuceHeader.h>

/**
 * CustomLookAndFeel: Modern visual style for the M7 reverb plugin
 * Provides sleek dark theme with custom knob/slider rendering
 */
class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel() override = default;

    // Color scheme
    static constexpr auto BACKGROUND_COLOR = 0xFF1a1a1a;
    static constexpr auto PANEL_COLOR = 0xFF2a2a2a;
    static constexpr auto ACCENT_COLOR = 0xFF00d9ff;
    static constexpr auto TEXT_COLOR = 0xFFffffff;
    static constexpr auto SLIDER_COLOR = 0xFF00d9ff;

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                         float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                         juce::Slider& slider) override;

    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                         float sliderPos, float minSliderPos, float maxSliderPos,
                         const juce::Slider::SliderStyle style, juce::Slider& slider) override;

    void drawLabel(juce::Graphics& g, juce::Label& label) override;

    void drawButtonBackground(juce::Graphics& g, juce::Button& button,
                             const juce::Colour& backgroundColour,
                             bool shouldDrawButtonAsHighlighted,
                             bool shouldDrawButtonAsDown) override;

    juce::Font getLabelFont(juce::Label& label) override;
    juce::Font getComboBoxFont(juce::ComboBox& box) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel)
};
