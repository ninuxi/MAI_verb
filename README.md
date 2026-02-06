# MAI_verb

**Professional Algorithmic Reverb Plugin**

A high-quality algorithmic reverb inspired by professional hardware processors, featuring an 8x8 Feedback Delay Network (FDN) for rich, natural-sounding reverb textures.

---

## 🎵 Overview

MAI_verb is a versatile reverb plugin that combines advanced DSP algorithms with an intuitive interface to deliver studio-quality reverb for music production, sound design, and audio post-production.

## 🎥 Demo Video

Watch and listen to MAI_verb in action:

<a href="https://youtu.be/uMFQvq_DFgA" target="_blank" rel="noopener noreferrer">
	<img alt="MAI_verb Demo Video" src="https://img.youtube.com/vi/uMFQvq_DFgA/hqdefault.jpg" />
</a>

<a href="https://youtu.be/uMFQvq_DFgA" target="_blank" rel="noopener noreferrer">Open the demo video on YouTube (new tab)</a>

## 🌟 Features

- **8x8 FDN Algorithm** - Complex, natural-sounding reverb texture
- **Early Reflections** - Realistic room simulation with customizable patterns
- **Modulation** - Add movement and shimmer effects
- **Integrated EQ** - Pre and post reverb tone shaping
- **Factory Presets** - Inspired by classic hardware reverbs
- **Low CPU Usage** - Optimized for real-time performance
- **Cross-Platform** - Available for macOS, Windows, and Linux

## 💿 Downloads

### [Latest Release v0.1](../../releases/tag/v0.1)

**Available Formats:**

| Platform | VST3 | AU | Standalone |
|----------|------|-----|------------|
| macOS (Universal) | ✅ | ✅ | ✅ |
| Windows (x64) | ✅ | - | ✅ |
| Linux (x64) | ✅ | - | ✅ |

## 📥 Installation

**⚠️ macOS Users: Important Code Signing Info**

This plugin is **ad-hoc signed** (free, no Apple Developer certificate). It's **100% safe**, but macOS Gatekeeper may block it without proper installation.

**Quick Install (macOS):**

```bash
# 1. Download and extract the ZIP
# 2. Open Terminal and navigate to the extracted folder
cd ~/Downloads/MAI_verb_*

# 3. Remove quarantine attributes (REQUIRED!)
xattr -cr *.vst3
xattr -cr *.component

# 4. Install plugins
cp -r *.vst3 ~/Library/Audio/Plug-Ins/VST3/
cp -r *.component ~/Library/Audio/Plug-Ins/Components/

# 5. Restart your DAW
```

**Full Installation Guides:**

- 🍎 **[macOS Installation Guide](INSTALL_INSTRUCTIONS.md)**
- 🪟 **[Windows Installation Guide](INSTALL_WINDOWS.md)**
- 🐧 **[Linux Installation Guide](INSTALL_LINUX.md)**

### Quick Install

**macOS (VST3):**
```bash
# Remove quarantine first
sudo xattr -rd com.apple.quarantine "MAI_verb.vst3"
# Then copy to plugins folder
cp -r "MAI_verb.vst3" ~/Library/Audio/Plug-Ins/VST3/
```

**Windows (VST3):**
```cmd
copy "MAI_verb.vst3" "C:\Program Files\Common Files\VST3\"
```

**Linux (VST3):**
```bash
cp -r "MAI_verb.vst3" ~/.vst3/
```

## 🎛️ Parameters

### Main Section
- **Mix** - Dry/Wet balance (0-100%)
- **Decay Time** - Reverb duration (0.1s - 30s)
- **Pre-Delay** - Initial delay before reverb onset (0-500ms)

### Size & Diffusion
- **Room Size** - Virtual room dimensions
- **Diffusion** - Reflection density and scattering

### Early Reflections
- **ER Level** - Early reflections volume
- **ER Pattern** - Room characteristic (Small, Medium, Large, Hall)

### Modulation
- **Mod Rate** - Modulation speed
- **Mod Depth** - Modulation intensity
- **Shimmer** - Pitch-shifted reverb effect

### EQ Section
- **Low Cut** - High-pass filter (20Hz-2kHz)
- **High Cut** - Low-pass filter (1kHz-20kHz)
- **Pre/Post** - EQ placement in signal chain

## 🎚️ DAW Compatibility

**Tested & Supported:**

### macOS
- Logic Pro / Logic Pro X
- Ableton Live
- FL Studio
- Reaper
- Studio One
- Cubase / Nuendo
- Pro Tools (VST3)

### Windows
- Ableton Live
- FL Studio
- Reaper
- Studio One
- Cubase / Nuendo
- Bitwig Studio

### Linux
- Reaper
- Bitwig Studio
- Ardour
- LMMS
- Tracktion Waveform

## 🔨 Building from Source

### Prerequisites
- CMake 3.22 or higher
- C++17 compatible compiler
- JUCE Framework (included)

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/[your-username]/MAI_verb.git
cd MAI_verb/BricastiM7_Clone

# Configure and build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

Detailed build instructions for each platform:
- [Build on macOS](INSTALL_INSTRUCTIONS.md)
- [Build on Windows](INSTALL_WINDOWS.md)
- [Build on Linux](INSTALL_LINUX.md)

## 📁 Project Structure

```
MAI_verb/
├── BricastiM7_Clone/          # Main plugin project
│   ├── Source/                 # Source code
│   │   ├── PluginProcessor.cpp # Audio processing
│   │   ├── PluginEditor.cpp    # GUI
│   │   └── DSP/                # DSP algorithms
│   │       ├── M7ReverbEngine.cpp
│   │       ├── FDN8x8.cpp
│   │       ├── EarlyReflections.cpp
│   │       └── M7Modulation.cpp
│   └── CMakeLists.txt          # Build configuration
├── JUCE/                       # JUCE framework
├── assets/                     # Images and resources
└── docs/                       # Documentation
```

## 🐛 Known Issues & Troubleshooting

### macOS Gatekeeper Issue
The plugin is not code-signed, so macOS will quarantine it. See [INSTALL_INSTRUCTIONS.md](INSTALL_INSTRUCTIONS.md) for the solution.

### Windows SmartScreen
Windows may block unsigned executables. Right-click → Properties → Check "Unblock"

### Linux VST3 Scan
Some DAWs may need manual VST3 path configuration. Add `~/.vst3/` to your DAW's plugin search paths.

For more issues, check the [Issues](../../issues) page.

## 🗺️ Roadmap

- [ ] AAX format for Pro Tools
- [ ] AUv3 for iOS
- [ ] Additional reverb algorithms
- [ ] MIDI control mapping
- [ ] Preset import/export
- [ ] Visual feedback display

## 📄 License

MIT License - See LICENSE file for details

## 👨‍💻 Author

**Mainenti**

## 🙏 Acknowledgments

- Built with [JUCE Framework](https://juce.com/)
- Inspired by professional hardware reverb processors
- Algorithm design influenced by classic digital reverb research

## 📮 Support & Contact

- **Issues**: [GitHub Issues](../../issues)
- **Discussions**: [GitHub Discussions](../../discussions)

---

**Current Version**: 0.1  
**Release Date**: February 2026  
**Minimum Requirements**: macOS 10.13+ / Windows 10+ / Modern Linux distro  

⭐ If you find MAI_verb useful, please consider starring the repository!
