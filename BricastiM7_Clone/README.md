# Bricasti M7 Clone - VST3/AU Plugin

Professional Bricasti M7 reverb clone built with JUCE.

## Features
- 19 M7 algorithms (Hall 1-7, Plate 1-5, Room 1-4, Chamber 1-3)
- 30 factory presets
- Multi-band decay control
- Modulation system
- Early reflections
- 7-band EQ
- Freeze mode
- Modern M7-style UI

## Requirements
- macOS 10.13+ (Intel/Apple Silicon)
- JUCE 7.0+
- Xcode 12+

## Quick Start

```bash
# 1. Clone and enter
cd ~/BricastiM7_Clone

# 2. Make build script executable
chmod +x build_m7.sh

# 3. Build (ensure JUCE_PATH is set)
./build_m7.sh

# 4. Install to DAW
cp -r Builds/MacOSX/build/Release/VST3/BricastiM7.vst3 ~/Library/Audio/Plug-Ins/VST3/