#!/bin/bash

# Quick Configuration Script for Riverberi M7
# Sets up environment for building with local JUCE

set -e

cd "$(dirname "$0")"

echo "🎵 Riverberi M7 - Configuration Setup"
echo ""

# Check JUCE
if [ -d "JUCE/modules/juce_core" ]; then
    echo "✓ JUCE framework found locally (./JUCE)"
    echo "  Modules: $(ls JUCE/modules | wc -l) detected"
    echo ""
    echo "Ready to build! Run:"
    echo "  ./build.sh -t Release -i"
    echo ""
else
    echo "⚠ JUCE framework not found at ./JUCE"
    echo ""
    echo "To fix, download JUCE from:"
    echo "  https://github.com/juce-framework/JUCE/releases"
    echo ""
    echo "Then extract to:"
    echo "  $(pwd)/JUCE"
    echo ""
    echo "Or set environment variable:"
    echo "  export JUCE_PATH=/path/to/JUCE"
    exit 1
fi
