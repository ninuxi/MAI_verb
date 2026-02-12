#!/bin/bash
set -e

VERSION="${1:-v0.1.1}"
RELEASE_NAME="MAI_verb_${VERSION}_Linux_x64"

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${GREEN}🚀 MAI_verb Linux Release Builder${NC}"
echo "Version: $VERSION"
echo "=================================="

echo -e "${YELLOW}🔧 Building plugins...${NC}"
./build.sh -p linux -t Release -i

echo -e "${YELLOW}📦 Creating release package...${NC}"
mkdir -p "releases/$RELEASE_NAME"

# Copy plugins from install directory
if [ -d "install/vst3" ]; then
    cp -r install/vst3/*.vst3 "releases/$RELEASE_NAME/"
    echo "✅ VST3 copied"
fi

if [ -d "install/lv2" ]; then
    cp -r install/lv2/*.lv2 "releases/$RELEASE_NAME/"
    echo "✅ LV2 copied"
fi

if [ -d "install/standalone" ]; then
    mkdir -p "releases/$RELEASE_NAME/Standalone"
    cp install/standalone/* "releases/$RELEASE_NAME/Standalone/"
    chmod +x "releases/$RELEASE_NAME/Standalone/"*
    echo "✅ Standalone copied"
fi

# Create user README
cat > "releases/$RELEASE_NAME/INSTALLATION.txt" << 'EOF'
═══════════════════════════════════════════════════════
  MAI_verb by Mainenti @ aiforlive
  Professional Algorithmic Reverb - Open Source
═══════════════════════════════════════════════════════

🐧 INSTALLAZIONE LINUX (Ubuntu/Debian)

╔═══════════════════════════════════════════════════╗
║  INSTALLAZIONE RAPIDA:                            ║
╚═══════════════════════════════════════════════════╝

1️⃣  Estrai il file ZIP scaricato

2️⃣  Apri il terminale nella cartella estratta:
    cd ~/Downloads/MAI_verb_*

3️⃣  Installa i plugin (utente):
    mkdir -p ~/.vst3 ~/.lv2 ~/.local/bin
    cp -r *.vst3 ~/.vst3/
    cp -r *.lv2 ~/.lv2/
    cp Standalone/* ~/.local/bin/
    chmod +x ~/.local/bin/*

4️⃣  Riavvia la tua DAW (Reaper, Ardour, Bitwig, etc.)

═══════════════════════════════════════════════════════

📦 FORMATI DISPONIBILI:

✅ VST3   - ~/.vst3/           (Reaper, Bitwig, etc.)
✅ LV2    - ~/.lv2/            (Ardour, Carla, etc.)
✅ Standalone - ~/.local/bin/  (Applicazione diretta)

═══════════════════════════════════════════════════════

🔧 INSTALLAZIONE SISTEMA (opzionale, richiede sudo):

sudo mkdir -p /usr/local/lib/vst3 /usr/local/lib/lv2
sudo cp -r *.vst3 /usr/local/lib/vst3/
sudo cp -r *.lv2 /usr/local/lib/lv2/
sudo cp Standalone/* /usr/local/bin/

═══════════════════════════════════════════════════════

📋 REQUISITI:

- Ubuntu 20.04+ / Debian 11+ (o compatibili)
- ALSA o JACK per l'audio
- Architettura x86_64

Dipendenze runtime (già installate nella maggior parte dei sistemi):
- libasound2, libjack (audio)
- libgtk-3-0, libwebkit2gtk-4.1 (GUI)
- libfreetype6, libx11-6 (grafica)

Se mancano, installa con:
  sudo apt install libasound2 libjack0 libgtk-3-0 \
       libwebkit2gtk-4.1-0 libfreetype6

═══════════════════════════════════════════════════════

🔧 RISOLUZIONE PROBLEMI

Problema: Plugin non caricato nella DAW

Soluzione:
  1. Verifica permessi: chmod -R 755 ~/.vst3/*.vst3
  2. Controlla dipendenze: ldd ~/.vst3/*.vst3/Contents/x86_64-linux/*.so
  3. Riavvia la DAW e forza il rescan dei plugin

Problema: Standalone non si avvia

Soluzione:
  1. Rendi eseguibile: chmod +x ~/.local/bin/"Bricasti M7"
  2. Verifica audio: assicurati che ALSA o JACK siano attivi

═══════════════════════════════════════════════════════

📄 LICENZA: Open Source (vedi LICENSE nel repository)
🔗 GitHub: https://github.com/ninuxi/MAI_verb
💬 Issues: https://github.com/ninuxi/MAI_verb/issues
👤 Autore: Mainenti @ aiforlive

═══════════════════════════════════════════════════════
EOF

# Create ZIP
cd releases
tar -czf "${RELEASE_NAME}.tar.gz" "$RELEASE_NAME"
zip -r "${RELEASE_NAME}.zip" "$RELEASE_NAME" -q

echo ""
echo -e "${GREEN}✅ Release Linux pronta!${NC}"
echo -e "   📁 releases/${RELEASE_NAME}.tar.gz"
echo -e "   📁 releases/${RELEASE_NAME}.zip"
