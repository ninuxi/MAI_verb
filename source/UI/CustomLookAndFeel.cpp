#include "UI/CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
    : juce::LookAndFeel_V4()
{
    // Set color scheme
    setColour(juce::ResizableWindow::backgroundColourId,
             juce::Colour(BACKGROUND_COLOR));
    setColour(juce::Label::textColourId,
             juce::Colour(TEXT_COLOR));
    setColour(juce::Slider::textBoxTextColourId,
             juce::Colour(TEXT_COLOR));
    setColour(juce::Slider::thumbColourId,
             juce::Colour(SLIDER_COLOR));
    setColour(juce::ComboBox::backgroundColourId,
             juce::Colour(PANEL_COLOR));
    setColour(juce::ComboBox::textColourId,
             juce::Colour(TEXT_COLOR));
    setColour(juce::ComboBox::outlineColourId,
             juce::Colour(ACCENT_COLOR));
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                                         float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                                         juce::Slider& slider)
{
    auto radius = (width < height ? width : height) / 2.0f;
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Draw background circle
    g.setColour(juce::Colour(PANEL_COLOR));
    g.fillEllipse(rx, ry, rw, rw);

    // Draw outline
    g.setColour(juce::Colour(ACCENT_COLOR));
    g.drawEllipse(rx, ry, rw, rw, 2.0f);

    // Draw fill arc
    juce::Path filledArc;
    filledArc.addCentredArc(centreX, centreY, radius - 4.0f, radius - 4.0f,
                           0.0f, rotaryStartAngle, angle, true);
    g.setColour(juce::Colour(SLIDER_COLOR));
    g.strokePath(filledArc, juce::PathStrokeType(4.0f, juce::PathStrokeType::curved));

    // Draw pointer
    juce::Path pointer;
    auto pointerLength = radius - 8.0f;
    auto pointerThickness = 3.0f;
    pointer.addRectangle(-pointerThickness / 2.0f, -radius + 4.0f,
                        pointerThickness, pointerLength);

    g.setColour(juce::Colour(SLIDER_COLOR));
    g.fillPath(pointer, juce::AffineTransform::rotation(angle)
                                     .translated(centreX, centreY));
}

void CustomLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                                        float sliderPos, float minSliderPos, float maxSliderPos,
                                        const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    if (style == juce::Slider::LinearBarVertical)
    {
        // Draw background
        g.setColour(juce::Colour(PANEL_COLOR));
        g.fillRect(x, y, width, height);

        // Draw outline
        g.setColour(juce::Colour(ACCENT_COLOR));
        g.drawRect(juce::Rectangle<int>(x, y, width, height), 1);

        // Draw fill
        auto fillHeight = (sliderPos - y) / (height) * height;
        g.setColour(juce::Colour(SLIDER_COLOR));
        g.fillRect(x, y + height - static_cast<int>(fillHeight), width,
                  static_cast<int>(fillHeight));
    }
    else if (style == juce::Slider::LinearHorizontal)
    {
        // Draw background
        g.setColour(juce::Colour(PANEL_COLOR));
        g.fillRect(x, y, width, height);

        // Draw outline
        g.setColour(juce::Colour(ACCENT_COLOR));
        g.drawRect(juce::Rectangle<int>(x, y, width, height), 1);

        // Draw fill
        auto fillWidth = ((sliderPos - x) / width) * width;
        g.setColour(juce::Colour(SLIDER_COLOR));
        g.fillRect(x, y, static_cast<int>(fillWidth), height);
    }
    else
    {
        // Linear slider (standard)
        auto trackX = x + 10;
        auto trackWidth = width - 20;
        auto trackY = y + height / 2 - 2;

        // Draw track
        g.setColour(juce::Colour(PANEL_COLOR));
        g.fillRect(trackX, trackY, trackWidth, 4);

        // Draw progress
        g.setColour(juce::Colour(SLIDER_COLOR));
        g.fillRect(trackX, trackY, static_cast<int>((sliderPos - trackX) / trackWidth * trackWidth), 4);

        // Draw thumb
        g.setColour(juce::Colour(ACCENT_COLOR));
        g.fillEllipse(sliderPos - 6, trackY - 4, 12, 12);
        g.setColour(juce::Colour(SLIDER_COLOR));
        g.drawEllipse(sliderPos - 6, trackY - 4, 12, 12, 2.0f);
    }
}

void CustomLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{
    g.fillAll(label.findColour(juce::Label::backgroundColourId));

    if (!label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const auto font = getLabelFont(label);

        g.setColour(label.findColour(juce::Label::textColourId).withAlpha(alpha));
        g.setFont(font);

        auto textArea = label.getBounds();

        g.drawFittedText(label.getText(), textArea, label.getJustificationType(),
                        juce::jmax(1, static_cast<int>(textArea.getHeight() / font.getHeight())),
                        label.getMinimumHorizontalScale());

        g.setColour(label.findColour(juce::Label::outlineColourId).withAlpha(alpha));
    }
    else if (label.isEnabled())
    {
        g.setColour(label.findColour(juce::Label::outlineColourId));
    }

    g.drawRect(label.getLocalBounds());
}

void CustomLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button,
                                            const juce::Colour& backgroundColour,
                                            bool shouldDrawButtonAsHighlighted,
                                            bool shouldDrawButtonAsDown)
{
    auto buttonArea = button.getLocalBounds();

    // Draw background
    auto fillColour = shouldDrawButtonAsDown ? juce::Colour(SLIDER_COLOR)
                                             : shouldDrawButtonAsHighlighted ? juce::Colour(0xFF00a8cc)
                                                                              : backgroundColour;
    g.setColour(fillColour);
    g.fillRoundedRectangle(buttonArea.toFloat(), 4.0f);

    // Draw border
    g.setColour(juce::Colour(ACCENT_COLOR));
    g.drawRoundedRectangle(buttonArea.toFloat(), 4.0f, 2.0f);
}

juce::Font CustomLookAndFeel::getLabelFont(juce::Label& label)
{
    return juce::Font(14.0f, juce::Font::bold);
}

juce::Font CustomLookAndFeel::getComboBoxFont(juce::ComboBox& box)
{
    return juce::Font(13.0f);
}
