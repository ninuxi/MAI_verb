# Riverberi M7 - Complete File Index

## Quick Navigation

### 📖 Start Here
- **START_HERE.txt** - Welcome guide and overview (read this first!)
- **QUICKSTART.md** - 5-minute setup instructions
- **README.md** - Complete documentation and features

### 🔧 Build & Setup
- **CMakeLists.txt** - CMake build configuration
- **quick_setup.sh** - Quick environment check
- **build.sh** - Automated cross-platform build script
- **setup.sh** - Development environment setup
- **build_diagnostics.sh** - System diagnostics and optimization tips
- **JuceProject.jucer** - Projucer project file (alternative build method)
- **JUCE/** - JUCE framework directory (required)

### 📚 Documentation
- **QUICKSTART.md** - 5 minutes to first build
- **README.md** - Full user guide and features
- **TECHNICAL.md** - Architecture, optimization, advanced topics
- **CHANGELOG.md** - Version history and future roadmap
- **PROJECT_SUMMARY.md** - Project overview and statistics
- **INDEX.md** - This file

### 💻 Source Code

#### Main Plugin Classes
- **source/include/PluginProcessor.h** - Main plugin audio processor header
- **source/PluginProcessor.cpp** - Plugin processor implementation
- **source/include/PluginEditor.h** - UI editor header
- **source/PluginEditor.cpp** - UI editor implementation

#### DSP Engine (Convolution & Audio Processing)
- **source/include/DSP/ConvolutionEngine.h** - Convolution reverb header
- **source/DSP/ConvolutionEngine.cpp** - Convolution engine implementation
- **source/include/DSP/IRLoader.h** - Impulse response loader header
- **source/DSP/IRLoader.cpp** - IR loading implementation
- **source/include/DSP/ParameterController.h** - Parameter management header
- **source/DSP/ParameterController.cpp** - Parameter system implementation
- **source/include/DSP/SampleRateConfig.h** - Multi-sample rate support
- **source/include/DSP/CrossPlatformUtils.h** - Cross-platform utilities

#### UI & Styling
- **source/include/UI/CustomLookAndFeel.h** - UI theme header
- **source/UI/CustomLookAndFeel.cpp** - Custom UI rendering

#### Data Files
- **source/Presets/M7Presets.xml** - 11 factory presets

### 📁 Directories

#### source/
```
source/
├── include/
│   ├── PluginProcessor.h
│   ├── PluginEditor.h
│   ├── DSP/
│   │   ├── ConvolutionEngine.h
│   │   ├── IRLoader.h
│   │   ├── ParameterController.h
│   │   ├── SampleRateConfig.h
│   │   └── CrossPlatformUtils.h
│   └── UI/
│       └── CustomLookAndFeel.h
├── PluginProcessor.cpp
├── PluginEditor.cpp
├── DSP/
│   ├── ConvolutionEngine.cpp
│   ├── IRLoader.cpp
│   └── ParameterController.cpp
├── UI/
│   └── CustomLookAndFeel.cpp
└── Presets/
    └── M7Presets.xml
```

#### IR_Samples/
User impulse response files directory
- **IR_Samples/README.md** - Guide for loading and creating IRs

#### build/ (After compilation)
Generated build artifacts

#### install/ (After installation)
Final compiled plugins ready for DAW

## File Statistics

| Category | Count |
|----------|-------|
| Header Files (.h) | 8 |
| Implementation Files (.cpp) | 8 |
| Documentation (.md) | 6 |
| Scripts (.sh) | 3 |
| Configuration Files | 3 |
| Preset Files (.xml) | 1 |
| Total Project Files | 30+ |
| Total Lines of Code | ~3,500 |
| Total Documentation Lines | ~2,000 |

## Architecture Overview

```
Riverberi M7 Plugin
├── Audio Input
│   ↓
├── PluginProcessor
│   ├── ParameterController (read parameters)
│   ├── ConvolutionEngine
│   │   ├── IRLoader (load impulse response)
│   │   ├── Pre-Delay Stage
│   │   ├── Time-Domain Convolution
│   │   └── Decay Scaling
│   └── Output Limiter
│   ↓
├── PluginEditor (UI)
│   ├── CustomLookAndFeel (dark theme)
│   ├── Parameter Sliders (9 controls)
│   ├── Preset Selector
│   └── IR Loader Button
│   ↓
└── Audio Output
```

## Key Features at a Glance

### DSP Features
- ✓ Time-domain convolution reverb
- ✓ Pre-delay (0-1000ms)
- ✓ Decay scaling (0.5-10s)
- ✓ Damping filter
- ✓ Stereo width control
- ✓ Early reflections
- ✓ Freeze mode
- ✓ Multi-sample rate support (44.1k-192k)

### UI Features
- ✓ Modern dark theme
- ✓ 9 automatable parameters
- ✓ Rotary knobs and sliders
- ✓ Preset management (11 factory)
- ✓ IR file loader
- ✓ Real-time information display

### Plugin Formats
- ✓ VST3 (Windows, macOS, Linux)
- ✓ AU (macOS)
- ✓ Standalone executable

## Build Command Reference

### Quick Build
```bash
./build.sh -t Release -i
```

### Diagnostic Check
```bash
./build_diagnostics.sh
```

### Setup Environment
```bash
./setup.sh
```

### Manual CMake Build
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel $(nproc)
```

## Documentation Purpose

| File | Purpose | Audience |
|------|---------|----------|
| START_HERE.txt | Welcome & orientation | Everyone |
| QUICKSTART.md | Fast setup | Beginners |
| README.md | Complete guide | Users |
| TECHNICAL.md | Deep dive | Developers |
| CHANGELOG.md | Version history | Developers |
| PROJECT_SUMMARY.md | Statistics | Managers |
| INDEX.md | File navigation | All (this file) |

## Common Tasks

### I want to build the plugin
→ Run: `./build.sh -t Release -i`

### I want to customize parameters
→ Edit: `source/include/DSP/ParameterController.h`

### I want to change the UI theme
→ Edit: `source/include/UI/CustomLookAndFeel.h`

### I want to add presets
→ Edit: `source/Presets/M7Presets.xml`

### I want to understand the architecture
→ Read: `TECHNICAL.md`

### I want to troubleshoot build issues
→ Run: `./build_diagnostics.sh`

### I want to load custom impulse responses
→ Read: `IR_Samples/README.md`

## Parameter Configuration

All parameters defined in:
- **File**: source/DSP/ParameterController.cpp
- **Method**: `createParameterLayout()`
- **Type**: AudioProcessorValueTreeState

To modify parameter ranges, edit the range in:
```cpp
juce::NormalisableRange<float>(min, max, step)
```

## UI Layout

Editor layout defined in:
- **File**: source/PluginEditor.cpp
- **Method**: `resized()`
- **Size**: 900x600 pixels (customizable)

## Preset System

Factory presets stored in:
- **File**: source/Presets/M7Presets.xml
- **Format**: XML with parameter ID/value pairs
- **Count**: 11 presets included
- **Add more**: Copy existing preset block and modify values

## Cross-Platform Support

Platform-specific code in:
- **File**: source/include/DSP/CrossPlatformUtils.h
- **Supported**: Windows, macOS, Linux
- **Plugin Path**: Handled automatically

## Real-Time Safety

Audio processing is real-time safe:
- No allocations in audio thread
- Lock-free parameter reading
- Pre-allocated buffers
- Zero-copy where possible

## Dependencies

- JUCE 7.0+ (required)
- CMake 3.22+ (for building)
- C++17 compiler
- Platform-specific tools (Xcode, MSVC, GCC)

No external audio libraries needed (JUCE handles all DSP).

## Version Information

- **Project**: Riverberi M7
- **Version**: 1.0.0
- **Framework**: JUCE 7.0+
- **Language**: C++17
- **Created**: January 2026

## Next Steps

1. Read **START_HERE.txt**
2. Run **./setup.sh**
3. Run **./build.sh -t Release -i**
4. Consult **README.md** for usage

Happy reverb creation! 🎵

---

For questions, refer to the appropriate documentation file above.
