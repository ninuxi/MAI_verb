#!/bin/bash

# Build script for Bricasti M7 on macOS
echo "🔧 Building Bricasti M7 Clone..."

# Check for JUCE
if [ -z "$JUCE_PATH" ]; then
    if [ -d "$HOME/JUCE" ]; then
        export JUCE_PATH="$HOME/JUCE"
        echo "Using JUCE at: $JUCE_PATH"
    else
        echo "❌ JUCE not found!"
        echo "Please set JUCE_PATH environment variable or install JUCE to ~/JUCE"
        echo "Download from: https://github.com/juce-framework/JUCE/releases"
        exit 1
    fi
fi

# Check for CMake
if ! command -v cmake &> /dev/null; then
    echo "❌ CMake not found!"
    echo "Please install CMake 3.22+"
    exit 1
fi

echo "🎛 Configuring build with CMake..."
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release

echo "🏗 Building plugins..."
cmake --build . --config Release

echo "✅ Build complete!"
echo ""
echo "📁 Output plugins:"
echo "   VST3: build/VST3/BricastiM7.vst3"
echo "   AU:   build/AU/BricastiM7.component"
echo ""
echo "🚀 To install to your DAW:"
echo "   cp -r build/VST3/BricastiM7.vst3 ~/Library/Audio/Plug-Ins/VST3/"
echo "   cp -r build/AU/BricastiM7.component ~/Library/Audio/Plug-Ins/Components/"