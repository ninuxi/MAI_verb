#!/bin/bash

# Script per creare un pacchetto da inviare al collega
# Include il plugin e lo script per rimuovere la quarantena

PACKAGE_NAME="Mainenti_Reverb_Package"
PACKAGE_DIR="$HOME/Desktop/$PACKAGE_NAME"

echo "=================================="
echo "Creazione Pacchetto Mainenti Reverb"
echo "=================================="

# Crea directory del pacchetto
rm -rf "$PACKAGE_DIR"
mkdir -p "$PACKAGE_DIR"

echo "Copio i file..."

# Copia il plugin compilato (cerca in varie posizioni)
BUILD_DIR="/Users/mainenti/make_plugin_riverberi/BricastiM7_Clone/build"

# Cerca VST3
if [ -d "$BUILD_DIR/VST3/Mainenti Reverb.vst3" ]; then
    cp -R "$BUILD_DIR/VST3/Mainenti Reverb.vst3" "$PACKAGE_DIR/"
    echo "✓ VST3 copiato"
elif [ -d "$BUILD_DIR/bin/VST3/Mainenti Reverb.vst3" ]; then
    cp -R "$BUILD_DIR/bin/VST3/Mainenti Reverb.vst3" "$PACKAGE_DIR/"
    echo "✓ VST3 copiato"
fi

# Cerca AU
if [ -d "$BUILD_DIR/AU/Mainenti Reverb.component" ]; then
    cp -R "$BUILD_DIR/AU/Mainenti Reverb.component" "$PACKAGE_DIR/"
    echo "✓ AU copiato"
elif [ -d "$BUILD_DIR/bin/AU/Mainenti Reverb.component" ]; then
    cp -R "$BUILD_DIR/bin/AU/Mainenti Reverb.component" "$PACKAGE_DIR/"
    echo "✓ AU copiato"
fi

# Cerca Standalone
if [ -d "$BUILD_DIR/bin/Standalone/Mainenti Reverb.app" ]; then
    cp -R "$BUILD_DIR/bin/Standalone/Mainenti Reverb.app" "$PACKAGE_DIR/"
    echo "✓ Standalone copiato"
fi

# Copia le istruzioni e lo script
cp "remove_quarantine.sh" "$PACKAGE_DIR/"
cp "INSTALL_INSTRUCTIONS.md" "$PACKAGE_DIR/LEGGIMI.md"
echo "✓ Istruzioni copiate"

# Crea un file di testo con istruzioni rapide
cat > "$PACKAGE_DIR/START_HERE.txt" << 'EOF'
MAINENTI REVERB - ISTRUZIONI RAPIDE
====================================

IMPORTANTE: Questo plugin non è firmato da Apple.
macOS Gatekeeper lo bloccherà.

SOLUZIONE RAPIDA:
1. Apri il Terminale
2. Trascina il file "remove_quarantine.sh" nel Terminale
3. Premi Invio

Oppure leggi LEGGIMI.md per istruzioni dettagliate.

INSTALLAZIONE:
- Copia "Mainenti Reverb.vst3" in ~/Library/Audio/Plug-Ins/VST3/
- Copia "Mainenti Reverb.component" in ~/Library/Audio/Plug-Ins/Components/
- Copia "Mainenti Reverb.app" in /Applications/

Poi esegui remove_quarantine.sh

====================================
EOF

echo "✓ File START_HERE.txt creato"

# Crea un archivio ZIP
cd "$HOME/Desktop"
zip -r "${PACKAGE_NAME}.zip" "$PACKAGE_NAME" > /dev/null 2>&1

echo ""
echo "=================================="
echo "✓ Pacchetto creato con successo!"
echo ""
echo "Posizione: $HOME/Desktop/${PACKAGE_NAME}.zip"
echo ""
echo "Invia questo file ZIP al tuo collega."
echo "=================================="
