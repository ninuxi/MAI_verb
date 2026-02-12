# Building MAI_verb on Windows

## Prerequisites

### 1. Install Visual Studio 2022
Download and install Visual Studio 2022 Community (free):
https://visualstudio.microsoft.com/downloads/

**Required components:**
- Desktop development with C++
- Windows 10 SDK (or later)
- CMake tools for Windows

### 2. Install CMake
Download CMake 3.22 or higher:
https://cmake.org/download/

Add CMake to PATH during installation.

### 3. Download JUCE Framework
JUCE is NOT included in the repository due to size.

**Option A: Git Clone (Recommended)**
```cmd
cd C:\path\to\MAI_verb-main
git clone https://github.com/juce-framework/JUCE.git JUCE
```

**Option B: Download ZIP**
1. Download from: https://github.com/juce-framework/JUCE/releases
2. Extract to `MAI_verb-main/JUCE/` directory

**Verify JUCE is in the correct location:**
```
MAI_verb-main/
├── JUCE/
│   ├── modules/
│   ├── extras/
│   └── CMakeLists.txt
├── BricastiM7_Clone/
└── CMakeLists.txt
```

## Building the Plugin

### Method 1: Using build.sh (Git Bash recommended)

If you have Git Bash installed:
```bash
./build.sh -p windows -t Release -i
```

The plugins will be in `install/vst3/` and `install/standalone/`

### Method 2: Manual CMake Build

Open **Developer Command Prompt for VS 2022**:

```cmd
# Navigate to project
cd C:\path\to\MAI_verb-main

# Create build directory
mkdir build
cd build

# Configure
cmake .. -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build . --config Release

# Find plugins in:
# build\RiverberoCloneM7_artefacts\Release\VST3\
# build\RiverberoCloneM7_artefacts\Release\Standalone\
```

## Creating Windows Release Package

### Using PowerShell:

```powershell
# Create release directory
$version = "v0.1.1"
$releaseName = "MAI_verb_${version}_Windows_x64"
mkdir "releases\$releaseName"

# Copy plugins
Copy-Item -Recurse "install\vst3\*.vst3" "releases\$releaseName\"
Copy-Item -Recurse "install\standalone\*" "releases\$releaseName\Standalone\"

# Create installation instructions
# (See INSTALL_WINDOWS.md)

# Create ZIP
Compress-Archive -Path "releases\$releaseName" -DestinationPath "releases\${releaseName}.zip"
```

## Troubleshooting

### CMake can't find JUCE
**Error:** `JUCE framework not found at ...`

**Solution:** Verify JUCE is in `MAI_verb-main/JUCE/` directory with correct structure.

### Visual Studio not found
**Error:** `Could not find Visual Studio`

**Solution:** 
1. Launch "Developer Command Prompt for VS 2022"
2. Or use `-G "Visual Studio 17 2022"` flag explicitly

### Missing Windows SDK
**Error:** `Windows SDK not found`

**Solution:** 
1. Open Visual Studio Installer
2. Modify installation
3. Add "Windows 10 SDK" or "Windows 11 SDK"

### Build fails with C++ errors
**Solution:**
1. Ensure C++ Desktop Development is installed
2. Use Visual Studio 2022 (not older versions)
3. Check that C++17 is enabled

## Plugin Formats

Windows build produces:
- **VST3**: `Bricasti M7.vst3` (folder bundle)
- **Standalone**: `Bricasti M7.exe`

**Note:** AU format is macOS only. LV2 is Linux only.

## Testing the Plugin

1. Copy VST3 to: `C:\Program Files\Common Files\VST3\`
2. Launch your DAW (Reaper, Ableton, FL Studio, etc.)
3. Rescan plugins
4. Load "Bricasti M7" or "MAI_verb"

## Release Checklist

- [ ] JUCE framework downloaded and in correct location
- [ ] Build completes without errors
- [ ] VST3 plugin validates in DAW
- [ ] Standalone application launches
- [ ] Audio processing works correctly
- [ ] Release package created with installation instructions
- [ ] ZIP file uploaded to GitHub Release

## Additional Resources

- [Windows Installation Guide](INSTALL_WINDOWS.md)
- [General Build Documentation](README.md#building-from-source)
- [JUCE Documentation](https://juce.com/learn/documentation)
