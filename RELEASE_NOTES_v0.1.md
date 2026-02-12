# MAI_verb v0.1 - Initial Release 🎉

First public release of **MAI_verb**, a professional algorithmic reverb plugin featuring an 8x8 Feedback Delay Network (FDN) for rich, natural-sounding reverb textures.

---

## ✨ Features

- **8x8 FDN Algorithm** - Complex, natural-sounding reverb texture
- **Early Reflections** - Realistic room simulation with customizable patterns  
- **Modulation Engine** - Add movement and shimmer effects
- **Integrated EQ** - Pre and post reverb tone shaping
- **Factory Presets** - Inspired by classic hardware reverbs
- **Low CPU Usage** - Optimized for real-time performance
- **Cross-Platform** - macOS, Windows, and Linux

---

## 💾 Available Downloads

### macOS (Universal Binary - Intel & Apple Silicon)
- ✅ **VST3** - All DAWs that support VST3
- ✅ **Audio Unit (AU)** - Logic Pro, GarageBand, etc.
- ✅ **Standalone App** - No DAW required

**Download**: `MAI_verb_v0.1_macOS.zip`

### Windows & Linux
Compile from source following the build instructions in the repository.

---

## 🚨 IMPORTANT - macOS Installation

macOS Gatekeeper will block the plugin because it's not code-signed by Apple.

### Quick Fix (Required on macOS):

After extracting the zip file, open Terminal and run:

```bash
# Remove quarantine from VST3
sudo xattr -rd com.apple.quarantine "MAI_verb.vst3"

# Remove quarantine from Audio Unit
sudo xattr -rd com.apple.quarantine "MAI_verb.component"

# Remove quarantine from Standalone
sudo xattr -rd com.apple.quarantine "MAI_verb.app"
```

**Or use the included script:**
```bash
./remove_quarantine.sh
```

Then copy to your plugins folder:
```bash
# VST3
cp -r "MAI_verb.vst3" ~/Library/Audio/Plug-Ins/VST3/

# Audio Unit
cp -r "MAI_verb.component" ~/Library/Audio/Plug-Ins/Components/

# Standalone
cp -r "MAI_verb.app" /Applications/
```

---

## 🪟 Windows Installation Notes

Windows SmartScreen may block the executable because it's not code-signed.

**To unblock:**

1. **Right-click** on the downloaded `.zip` file
2. Select **Properties** 
3. Check **"Unblock"** at the bottom
4. Click **Apply** → **OK**
5. Extract the zip file

**Or after extraction:**
```cmd
# Remove quarantine using PowerShell
Unblock-File -Path "MAI_verb.vst3" -Confirm:$false
```

Then copy to:
```
C:\Program Files\Common Files\VST3\
```

---

## 🐧 Linux Installation

```bash
# Install to user VST3 folder
cp -r "MAI_verb.vst3" ~/.vst3/

# Or system-wide (requires sudo)
sudo cp -r "MAI_verb.vst3" /usr/local/lib/vst3/

# Make sure it's executable
chmod -R 755 ~/.vst3/MAI_verb.vst3
```

---

## 🎛️ Quick Start

1. **Remove quarantine** (macOS) or **unblock** (Windows)
2. **Install** the plugin to your DAW's plugin folder
3. **Rescan** plugins in your DAW
4. **Load** MAI_verb on your track
5. **Choose** a factory preset or start tweaking!

---

## 📋 System Requirements

| Platform | Minimum Requirements |
|----------|---------------------|
| **macOS** | macOS 10.13 (High Sierra) or newer |
| **Windows** | Windows 10 64-bit or newer |
| **Linux** | Modern distribution (glibc 2.27+) |

---

## 🎚️ Main Parameters

- **Mix** - Dry/Wet balance
- **Decay Time** - Reverb duration (0.1s - 30s)
- **Pre-Delay** - Initial delay before reverb
- **Room Size** - Virtual room dimensions
- **Diffusion** - Reflection density
- **Early Reflections** - Volume and pattern
- **Modulation** - Rate, Depth, and Shimmer
- **EQ** - Low/High cut filters

---

## 🐛 Known Issues

- Plugin is **not code-signed** (macOS Gatekeeper / Windows SmartScreen warnings)
- No **AAX** format yet (Pro Tools users use VST3 version)
- No preset **import/export** functionality yet

---

## 🗺️ Roadmap

- [ ] AAX format support
- [ ] AUv3 for iOS
- [ ] Additional reverb algorithms
- [ ] MIDI control mapping
- [ ] Enhanced preset management
- [ ] Visual feedback display

---

## 📚 Documentation

- [Installation Guide - macOS](https://github.com/ninuxi/MAI_verb/blob/main/INSTALL_INSTRUCTIONS.md)
- [Installation Guide - Windows](https://github.com/ninuxi/MAI_verb/blob/main/INSTALL_WINDOWS.md)
- [Installation Guide - Linux](https://github.com/ninuxi/MAI_verb/blob/main/INSTALL_LINUX.md)
- [Build from Source](https://github.com/ninuxi/MAI_verb#building-from-source)

---

## 🙏 Acknowledgments

- Built with **JUCE Framework**
- Inspired by professional hardware reverb processors
- Algorithm design influenced by classic digital reverb research

---

## 📮 Support

- **Issues**: [GitHub Issues](https://github.com/ninuxi/MAI_verb/issues)
- **Discussions**: [GitHub Discussions](https://github.com/ninuxi/MAI_verb/discussions)

---

**Version**: 0.1  
**Release Date**: February 6, 2026  
**License**: MIT

⭐ If you find MAI_verb useful, please star the repository!
