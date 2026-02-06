#pragma once
#include <juce_dsp/juce_dsp.h>

/**
 * M7Modulation: Stub class.
 * Modulation is now integrated directly into the FDN8x8 delay lines
 * as read-position modulation (chorus-like pitch variation).
 * This file is kept for build compatibility.
 */
class M7Modulation
{
public:
    M7Modulation() {}
    void prepare(double /*sampleRate*/) {}
    void process(float& /*left*/, float& /*right*/) {}
    void reset() {}
    void setRate(float /*rate*/) {}
    void setDepth(float /*depth*/) {}
};
