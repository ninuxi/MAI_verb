#pragma once
#include <JuceHeader.h>

class M7LookAndFeel : public juce::LookAndFeel_V4
{
public:
    M7LookAndFeel();
    
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                         float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                         juce::Slider& slider) override;
    
    void drawButtonBackground(juce::Graphics& g, juce::Button& button,
                             const juce::Colour& backgroundColour,
                             bool isMouseOverButton, bool isButtonDown) override;
    
    juce::Font getLabelFont(juce::Label& label) override;
    
private:
    juce::Colour panelColor = juce::Colour(0xFF1A1A1A);
    juce::Colour accentColor = juce::Colour(0xFF00FF00);
    juce::Colour textColor = juce::Colour(0xFFCCCCCC);
};