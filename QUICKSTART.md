# Riverberi M7 Quick Start Guide

## 5-Minute Setup

### 1. Prerequisites

Ensure JUCE framework is in the `JUCE/` directory:

```bash
# You should have this structure:
# make_plugin_riverberi/
# ├── JUCE/                    (JUCE framework)
# ├── source/                  (plugin source code)
# ├── CMakeLists.txt
# └── build.sh
```

If JUCE is elsewhere, set environment variable:
```bash
export JUCE_PATH=/path/to/JUCE
```

Verify CMake is installed:
```bash
cmake --version  # Should be 3.22+
```

### 2. Build Plugin

**Easy (using build script):**
```bash
chmod +x build.sh
./build.sh -t Release -i
```

**Manual (CMake):**
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### 3. Install to DAW

Locate built plugin:
- macOS: `install/vst3/RiverberiM7.vst3` or `Builds/MacOSX/build/Release/RiverberiM7.component`
- Windows: `install/vst3/RiverberiM7.dll`
- Linux: `install/vst3/RiverberiM7.so`

Copy to your DAW's plugin directory or use symlink.

### 4. Load in DAW

1. Rescan plugins in your DAW
2. Add Riverberi M7 to track/master
3. Click "Load IR" and select a WAV file
4. Adjust parameters with sliders

## Common Tasks

### Load Custom IR

```
Click "Load IR" → Select WAV/AIFF file → Adjust decay/pre-delay
```

### Save Preset

```
Adjust parameters → Click "Save Preset" → Enter name
```

### Change Sample Rate

Plugin auto-detects and adjusts. No configuration needed.

### Monitor CPU

Display shows real-time CPU load in UI corner.

## Troubleshooting

| Issue | Solution |
|-------|----------|
| Plugin not found | Check DAW plugin path matches build output |
| Crackling | Increase buffer size in DAW |
| No sound | Load an IR file, check Mix slider > 0% |
| Build fails (JUCE not found) | Ensure JUCE is in ./JUCE directory or set JUCE_PATH |
| CMake error | Update CMake to 3.22+ |

## File Structure After Build

```
make_plugin_riverberi/
├── build/              # CMake build output
├── install/            # Built plugins (after -i flag)
│   └── vst3/RiverberiM7.vst3
├── source/             # Source code
├── build.sh            # Build script
├── CMakeLists.txt      # Build configuration
└── README.md           # Full documentation
```

## Next Steps

1. **Customize presets**: Edit `source/Presets/M7Presets.xml`
2. **Enhance UI**: Modify `source/include/UI/CustomLookAndFeel.h`
3. **Add features**: See `TECHNICAL.md` for architecture
4. **Optimize**: Check performance with build profiling

## Resources

- JUCE Documentation: https://docs.juce.com
- VST3 Spec: https://github.com/steinbergmedia/vst3_public_sdk
- Impulse Responses: http://www.openair.hosted.york.ac.uk/

---

Need help? Check README.md or TECHNICAL.md
