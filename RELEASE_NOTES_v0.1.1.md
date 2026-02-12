# Release Notes - MAI_verb v0.1.1

## 🎉 What's New

### Linux Support Added! 🐧
- Full Linux builds now available (Ubuntu 20.04+, Debian 11+)
- VST3, LV2, and Standalone formats
- Tested on Ubuntu 24.04

### Improvements
- Updated CMake configuration for cross-platform builds
- Added proper LV2 URI for Linux plugin hosts
- Enhanced build scripts for multi-platform support

## 📦 Available Downloads

### macOS (M1+)
- `MAI_verb_v0.1.1_macOS.zip`
  - VST3 (Universal Binary)
  - AU (Audio Unit)
  - Standalone app
  - Ad-hoc signed (see installation instructions)

### Linux (x86_64)
- `MAI_verb_v0.1.1_Linux_x64.tar.gz` / `.zip`
  - VST3 bundle
  - LV2 bundle
  - Standalone executable
  - Compatible with Reaper, Ardour, Bitwig, LMMS

### Windows (x64)
- `MAI_verb_v0.1.1_Windows_x64.zip`
  - VST3 bundle
  - Standalone executable
  - Compatible with all modern DAWs (Ableton, FL Studio, Reaper, etc.)

## 📋 Installation

### macOS
```bash
cd ~/Downloads/MAI_verb_*
xattr -cr *.vst3 *.component
cp -r *.vst3 ~/Library/Audio/Plug-Ins/VST3/
cp -r *.component ~/Library/Audio/Plug-Ins/Components/
```

### Linux
```bash
tar -xzf MAI_verb_v0.1.1_Linux_x64.tar.gz
cd MAI_verb_*
mkdir -p ~/.vst3 ~/.lv2 ~/.local/bin
cp -r *.vst3 ~/.vst3/
cp -r *.lv2 ~/.lv2/
cp Standalone/* ~/.local/bin/
chmod +x ~/.local/bin/*
```

### Windows
```
1. Extract MAI_verb_v0.1.1_Windows_x64.zip
2. Copy "Bricasti M7.vst3" to: C:\Program Files\Common Files\VST3\
3. Restart your DAW and rescan plugins
```

Full installation guides:
- [macOS](INSTALL_INSTRUCTIONS.md)
- [Linux](INSTALL_LINUX.md)
- [Windows](INSTALL_WINDOWS.md)

## 🎛️ Features

- **Professional Reverb Algorithm**: 8x8 Feedback Delay Network (FDN)
- **Early Reflections**: Realistic room simulation
- **Modulation**: Add movement and shimmer to reverb tail
- **Integrated EQ**: Pre/post reverb tone shaping
- **Low CPU Usage**: Optimized for real-time performance
- **Factory Presets**: Classic hardware-inspired settings

## 🐛 Known Issues

- macOS: Requires removing quarantine attributes (see install guide)
- Linux: May require manual VST3/LV2 path configuration in some DAWs
- Windows: May trigger SmartScreen warning (not code-signed)

## 💡 Requirements

### macOS
- macOS 10.13+ (High Sierra or later)
- Apple Silicon (M1/M2/M3) or Intel
- Host that supports VST3, AU, or Standalone

### Linux
- Ubuntu 20.04+ / Debian 11+ or compatible
- x86_64 architecture
- ALSA or JACK for audio
- Runtime dependencies: libasound2, libjack, libgtk-3-0, libwebkit2gtk-4.1

## 🔗 Links

- [GitHub Repository](https://github.com/ninuxi/MAI_verb)
- [Report Issues](https://github.com/ninuxi/MAI_verb/issues)
- [Documentation](https://github.com/ninuxi/MAI_verb#readme)

## 📄 License

Open Source - MIT License

---

**Full Changelog**: https://github.com/ninuxi/MAI_verb/compare/v0.1...v0.1.1
