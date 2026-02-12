#!/bin/bash
set -e

VERSION="${1:-v0.1.1}"
RELEASE_NAME="MAI_verb_${VERSION}_macOS"

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${GREEN}🚀 MAI_verb Release Builder${NC}"
echo "Version: $VERSION"
echo "=================================="

echo -e "${YELLOW}🔧 Building plugins...${NC}"
cd BricastiM7_Clone
./build_m7.sh
cd ..

echo -e "${YELLOW}🔐 Signing plugins (ad-hoc, free)...${NC}"
./sign_plugins.sh

echo -e "${YELLOW}📦 Creating release package...${NC}"
mkdir -p "releases/$RELEASE_NAME"

# Find and copy plugins
VST3=$(find BricastiM7_Clone/build -name "*.vst3" -type d | head -1)
AU=$(find BricastiM7_Clone/build -name "*.component" -type d | head -1)

if [ -n "$VST3" ]; then
    cp -r "$VST3" "releases/$RELEASE_NAME/"
    echo "✅ VST3 copied"
fi

if [ -n "$AU" ]; then
    cp -r "$AU" "releases/$RELEASE_NAME/"
    echo "✅ AU copied"
fi

# Create user README
cat > "releases/$RELEASE_NAME/INSTALLATION.txt" << 'EOF'
═══════════════════════════════════════════════════════
  MAI_verb by Mainenti @ aiforlive
  Professional Algorithmic Reverb - Open Source
═══════════════════════════════════════════════════════

⚠️  IMPORTANTE PER UTENTI macOS ⚠️

Questo plugin è firmato localmente (ad-hoc) e NON ha un
certificato Apple Developer. È SICURO da usare.

╔═══════════════════════════════════════════════════╗
║  INSTALLAZIONE - SEGUI QUESTI PASSAGGI:          ║
╚═══════════════════════════════════════════════════╝

1️⃣  Apri il Terminale (Spotlight → "Terminale")

2️⃣  Vai nella cartella dove hai estratto i file:
    cd ~/Downloads/MAI_verb_*

3️⃣  RIMUOVI LA QUARANTENA (OBBLIGATORIO):
    xattr -cr *.vst3
    xattr -cr *.component

4️⃣  Installa i plugin:
    cp -r *.vst3 ~/Library/Audio/Plug-Ins/VST3/
    cp -r *.component ~/Library/Audio/Plug-Ins/Components/

5️⃣  Riavvia la tua DAW (Ableton, Logic, Reaper, etc.)

═══════════════════════════════════════════════════════

🔧 RISOLUZIONE PROBLEMI

Problema: "Il plugin non può essere aperto"

Soluzione:
  xattr -cr ~/Library/Audio/Plug-Ins/VST3/*.vst3
  xattr -cr ~/Library/Audio/Plug-Ins/Components/*.component

Poi riavvia la DAW.

═══════════════════════════════════════════════════════

📄 LICENZA: Open Source (vedi LICENSE nel repository)
🔗 GitHub: https://github.com/ninuxi/MAI_verb
💬 Issues: https://github.com/ninuxi/MAI_verb/issues
👤 Autore: Mainenti @ aiforlive

═══════════════════════════════════════════════════════
EOF

# Create ZIP
cd releases
zip -r "${RELEASE_NAME}.zip" "$RELEASE_NAME" -q

echo ""
echo -e "${GREEN}✅ Release pronta!${NC}"
echo -e "   📁 releases/${RELEASE_NAME}.zip"
echo ""
echo -e "${YELLOW}📤 Prossimi passi:${NC}"
echo "   1. Vai su https://github.com/ninuxi/MAI_verb/releases"
echo "   2. Clicca 'Draft a new release'"
echo "   3. Tag: $VERSION"
echo "   4. Carica: releases/${RELEASE_NAME}.zip"
echo "   5. Pubblica!"
