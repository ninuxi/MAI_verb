#include <iostream>
#include "DSP/M7ReverbEngine.h"

int main() {
    M7ReverbEngine reverb;
    reverb.prepare(44100.0, 512);
    
    juce::AudioBuffer<float> buffer(2, 512);
    buffer.clear();
    buffer.setSample(0, 0, 1.0f); // Impulse
    
    reverb.process(buffer);
    
    std::cout << "Output L: " << buffer.getSample(0, 0) << std::endl;
    std::cout << "Output R: " << buffer.getSample(1, 0) << std::endl;
    
    return 0;
}