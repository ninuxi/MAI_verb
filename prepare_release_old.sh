#!/bin/bash

# Script per preparare la release 0.1 di MAI_verb
# Crea pacchetti separati per macOS, Windows, e Linux

VERSION="0.1"
RELEASE_DIR="$HOME/Desktop/MAI_verb_Release_v${VERSION}"
BUILD_DIR="/Users/mainenti/make_plugin_riverberi/BricastiM7_Clone/build"

echo "════════════════════════════════════════"
echo "   MAI_verb Release ${VERSION} Builder   "
echo "════════════════════════════════════════"
echo ""

# Pulisci e crea directory di release
rm -rf "$RELEASE_DIR"
mkdir -p "$RELEASE_DIR"

# Colori
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

# ============================================
# Pacchetto macOS
# ============================================
echo -e "${BLUE}📦 Creazione pacchetto macOS...${NC}"

MACOS_DIR="$RELEASE_DIR/MAI_verb_v${VERSION}_macOS"
mkdir -p "$MACOS_DIR"

# Copia plugin macOS
if [ -d "$BUILD_DIR/lib/VST3/Mainenti Reverb.vst3" ]; then
    cp -R "$BUILD_DIR/lib/VST3/Mainenti Reverb.vst3" "$MACOS_DIR/MAI_verb.vst3"
    echo -e "${GREEN}✓${NC} VST3 copiato"
fi

if [ -d "$BUILD_DIR/lib/AU/Mainenti Reverb.component" ]; then
    cp -R "$BUILD_DIR/lib/AU/Mainenti Reverb.component" "$MACOS_DIR/MAI_verb.component"
    echo -e "${GREEN}✓${NC} AU copiato"
fi

if [ -d "$BUILD_DIR/bin/Standalone/Mainenti Reverb.app" ]; then
    cp -R "$BUILD_DIR/bin/Standalone/Mainenti Reverb.app" "$MACOS_DIR/MAI_verb.app"
    echo -e "${GREEN}✓${NC} Standalone copiato"
fi

# Aggiungi documentazione
cp INSTALL_INSTRUCTIONS.md "$MACOS_DIR/READ_ME.md"
cp remove_quarantine.sh "$MACOS_DIR/"

# Crea istruzioni rapide
cat > "$MACOS_DIR/INSTALL.txt" << 'EOF'
MAI_verb v0.1 - macOS Installation
===================================

IMPORTANT: Remove Gatekeeper quarantine first!

Quick Install:
1. Run: ./remove_quarantine.sh
2. Copy VST3: cp -r MAI_verb.vst3 ~/Library/Audio/Plug-Ins/VST3/
3. Copy AU: cp -r MAI_verb.component ~/Library/Audio/Plug-Ins/Components/
4. Copy Standalone: cp -r MAI_verb.app /Applications/

Read READ_ME.md for detailed instructions.
EOF

# Crea archivio macOS
cd "$RELEASE_DIR"
zip -r "MAI_verb_v${VERSION}_macOS.zip" "MAI_verb_v${VERSION}_macOS" > /dev/null 2>&1
echo -e "${GREEN}✓${NC} Archivio macOS creato"

# ============================================
# Template per Windows (note per compilazione)
# ============================================
echo ""
echo -e "${BLUE}📝 Creazione template Windows...${NC}"

WINDOWS_DIR="$RELEASE_DIR/MAI_verb_v${VERSION}_Windows"
mkdir -p "$WINDOWS_DIR"

cp INSTALL_WINDOWS.md "$WINDOWS_DIR/READ_ME.md"

cat > "$WINDOWS_DIR/BUILD_INSTRUCTIONS.txt" << 'EOF'
MAI_verb v0.1 - Windows Build Instructions
===========================================

To build for Windows, you need to compile on a Windows machine:

Requirements:
- Visual Studio 2019 or newer
- CMake 3.22+
- Git

Build Steps:
1. Open Developer Command Prompt for VS
2. cd BricastiM7_Clone
3. mkdir build && cd build
4. cmake .. -G "Visual Studio 17 2022"
5. cmake --build . --config Release

Output files will be in:
- build/BricastiM7_artefacts/Release/VST3/MAI_verb.vst3
- build/BricastiM7_artefacts/Release/Standalone/MAI_verb.exe

Installation:
- Copy MAI_verb.vst3 to C:\Program Files\Common Files\VST3\
- Copy MAI_verb.exe to desired location

See READ_ME.md for detailed instructions.
EOF

echo -e "${YELLOW}⚠${NC}  Windows: Richiede compilazione su Windows"

# ============================================
# Template per Linux (note per compilazione)
# ============================================
echo ""
echo -e "${BLUE}📝 Creazione template Linux...${NC}"

LINUX_DIR="$RELEASE_DIR/MAI_verb_v${VERSION}_Linux"
mkdir -p "$LINUX_DIR"

cp INSTALL_LINUX.md "$LINUX_DIR/READ_ME.md"

cat > "$LINUX_DIR/BUILD_INSTRUCTIONS.txt" << 'EOF'
MAI_verb v0.1 - Linux Build Instructions
=========================================

To build for Linux:

Install Dependencies (Ubuntu/Debian):
sudo apt install build-essential cmake git pkg-config \
    libasound2-dev libjack-jackd2-dev \
    libfreetype6-dev libx11-dev libxrandr-dev libxinerama-dev \
    libxcursor-dev libgl1-mesa-dev libwebkit2gtk-4.0-dev

Build Steps:
cd BricastiM7_Clone
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

Output files will be in:
- build/BricastiM7_artefacts/VST3/MAI_verb.vst3
- build/BricastiM7_artefacts/Standalone/MAI_verb

Installation:
cp -r build/BricastiM7_artefacts/VST3/MAI_verb.vst3 ~/.vst3/
cp build/BricastiM7_artefacts/Standalone/MAI_verb ~/.local/bin/

See READ_ME.md for detailed instructions.
EOF

echo -e "${YELLOW}⚠${NC}  Linux: Richiede compilazione su Linux"

# ============================================
# Crea README per la release
# ============================================
cat > "$RELEASE_DIR/RELEASE_NOTES.md" << 'EOF'
# MAI_verb v0.1 - Release Notes

## First Release

This is the initial release of MAI_verb, a professional algorithmic reverb plugin.

### Features
- 8x8 Feedback Delay Network (FDN) algorithm
- Early reflections simulation
- Modulation and shimmer effects
- Integrated pre/post EQ
- Factory presets
- Cross-platform support

### Available Formats

#### macOS (Universal Binary)
- ✅ VST3
- ✅ Audio Unit (AU)
- ✅ Standalone App
- **Ready to use** - Download and install

#### Windows (x64)
- ⚠️ VST3 (requires Windows compilation)
- ⚠️ Standalone (requires Windows compilation)
- Template and instructions provided

#### Linux (x64)
- ⚠️ VST3 (requires Linux compilation)
- ⚠️ Standalone (requires Linux compilation)
- Template and instructions provided

### Installation

See platform-specific README files in each package.

**Important for macOS users:** Remove Gatekeeper quarantine before use!
Run: `sudo xattr -rd com.apple.quarantine MAI_verb.vst3`

### System Requirements

- **macOS**: 10.13 (High Sierra) or newer
- **Windows**: Windows 10 or newer, 64-bit
- **Linux**: Modern distribution with glibc 2.27+

### Known Issues

- Plugin is not code-signed (macOS Gatekeeper warning)
- No AAX format yet
- No preset import/export

### Coming Soon

- AAX format for Pro Tools
- Additional reverb algorithms
- Preset management
- MIDI mapping

---

**Release Date**: February 2026
**License**: [Your License]

For issues and support: https://github.com/[your-username]/MAI_verb/issues
EOF

# ============================================
# Crea script per GitHub Release
# ============================================
cat > "$RELEASE_DIR/github_release_commands.txt" << EOF
GitHub Release v0.1 - Commands Reference
=========================================

1. Create GitHub Repository:
   - Go to: https://github.com/new
   - Repository name: MAI_verb
   - Description: Professional Algorithmic Reverb Plugin
   - Public/Private: Your choice
   - Initialize with README: NO (we have our own)

2. Initialize local repository:
   cd /Users/mainenti/make_plugin_riverberi
   git init
   git add .
   git commit -m "Initial commit - MAI_verb v0.1"
   git branch -M main
   git remote add origin https://github.com/[your-username]/MAI_verb.git
   git push -u origin main

3. Create Release on GitHub:
   - Go to: https://github.com/[your-username]/MAI_verb/releases/new
   - Tag version: v0.1
   - Release title: MAI_verb v0.1 - Initial Release
   - Description: Copy from RELEASE_NOTES.md
   - Attach files:
     * MAI_verb_v0.1_macOS.zip
     * MAI_verb_v0.1_Windows.zip (when compiled)
     * MAI_verb_v0.1_Linux.zip (when compiled)

4. Or use GitHub CLI:
   gh release create v0.1 \\
     --title "MAI_verb v0.1 - Initial Release" \\
     --notes-file RELEASE_NOTES.md \\
     MAI_verb_v0.1_macOS.zip

Files to upload:
- ${RELEASE_DIR}/MAI_verb_v0.1_macOS.zip (✓ Ready)
- ${RELEASE_DIR}/MAI_verb_v0.1_Windows.zip (Compile on Windows first)
- ${RELEASE_DIR}/MAI_verb_v0.1_Linux.zip (Compile on Linux first)
EOF

# ============================================
# Summary
# ============================================
echo ""
echo "════════════════════════════════════════"
echo -e "${GREEN}✓ Release preparata con successo!${NC}"
echo "════════════════════════════════════════"
echo ""
echo "Directory release: $RELEASE_DIR"
echo ""
echo "📦 Pacchetti creati:"
echo "  ✓ macOS (completo)"
echo "  ⚠ Windows (template - richiede compilazione)"
echo "  ⚠ Linux (template - richiede compilazione)"
echo ""
echo "📝 Prossimi passi:"
echo "  1. Leggi: $RELEASE_DIR/github_release_commands.txt"
echo "  2. Crea repository GitHub 'MAI_verb'"
echo "  3. Push del codice"
echo "  4. Crea release v0.1 su GitHub"
echo "  5. Carica MAI_verb_v0.1_macOS.zip"
echo ""
echo "Per Windows e Linux:"
echo "  - Compila su quelle piattaforme"
echo "  - Aggiungi i file compilati alla release"
echo ""
echo "════════════════════════════════════════"
