#include "M7LookAndFeel.h"

M7LookAndFeel::M7LookAndFeel()
{
    setColour(juce::Slider::rotarySliderFillColourId, accentColor);
    setColour(juce::Slider::thumbColourId, accentColor.brighter());
    setColour(juce::Slider::textBoxTextColourId, textColor);
    setColour(juce::Slider::textBoxBackgroundColourId, panelColor.darker());
    setColour(juce::Slider::textBoxOutlineColourId, accentColor);
    setColour(juce::Label::textColourId, textColor);
    setColour(juce::ComboBox::backgroundColourId, panelColor.darker());
    setColour(juce::ComboBox::textColourId, textColor);
    setColour(juce::ComboBox::arrowColourId, accentColor);
    setColour(juce::ToggleButton::textColourId, textColor);
    setColour(juce::ToggleButton::tickColourId, accentColor);
}

void M7LookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                                    float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                                    juce::Slider& slider)
{
    auto radius = juce::jmin(width / 2, height / 2) - 4.0f;
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    // Draw background circle
    g.setColour(panelColor.darker());
    g.fillEllipse(rx, ry, rw, rw);
    
    // Draw outline
    g.setColour(accentColor.withAlpha(0.3f));
    g.drawEllipse(rx, ry, rw, rw, 2.0f);
    
    // Draw filled arc
    juce::Path filledArc;
    filledArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, 0.0f);
    g.setColour(accentColor.withAlpha(0.5f));
    g.fillPath(filledArc);
    
    // Draw pointer
    juce::Path p;
    auto pointerLength = radius * 0.75f;
    auto pointerThickness = 3.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
    g.setColour(accentColor.brighter());
    g.fillPath(p);
    
    // Draw center dot
    g.setColour(panelColor.brighter());
    g.fillEllipse(centreX - 3.0f, centreY - 3.0f, 6.0f, 6.0f);
}

void M7LookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button,
                                        const juce::Colour& backgroundColour,
                                        bool isMouseOverButton, bool isButtonDown)
{
    auto bounds = button.getLocalBounds().toFloat().reduced(1.0f);
    auto cornerSize = 4.0f;
    
    g.setColour(backgroundColour.withAlpha(button.isEnabled() ? 0.8f : 0.4f));
    g.fillRoundedRectangle(bounds, cornerSize);
    
    g.setColour(accentColor.withAlpha(isMouseOverButton ? 0.8f : 0.4f));
    g.drawRoundedRectangle(bounds, cornerSize, 2.0f);
    
    if (isButtonDown)
    {
        g.setColour(accentColor.withAlpha(0.2f));
        g.fillRoundedRectangle(bounds, cornerSize);
    }
}

juce::Font M7LookAndFeel::getLabelFont(juce::Label& label)
{
    return juce::Font(14.0f, juce::Font::plain);
}