#!/bin/bash

# Script per rimuovere la quarantena Gatekeeper dai plugin Mainenti Reverb
# Eseguire questo script dopo aver installato i plugin

echo "=================================="
echo "Mainenti Reverb - Rimozione Quarantena"
echo "=================================="
echo ""

# Colori per output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Funzione per rimuovere quarantena
remove_quarantine() {
    local path="$1"
    local name="$2"
    
    if [ -e "$path" ]; then
        echo -n "Rimuovo quarantena da $name... "
        # Prima prova senza sudo (solo attributo quarantena)
        xattr -rd com.apple.quarantine "$path" 2>/dev/null
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}✓ OK${NC}"
            return 0
        else
            # Se fallisce, prova con sudo
            sudo xattr -rd com.apple.quarantine "$path" 2>/dev/null
            if [ $? -eq 0 ]; then
                echo -e "${GREEN}✓ OK (con sudo)${NC}"
                return 0
            else
                echo -e "${RED}✗ ERRORE${NC}"
                return 1
            fi
        fi
    else
        echo -e "${YELLOW}⚠ $name non trovato in: $path${NC}"
        return 2
    fi
}

# Cerca nelle posizioni comuni
echo "Cerco i plugin installati..."
echo ""

# VST3 nelle posizioni comuni
remove_quarantine "/Library/Audio/Plug-Ins/VST3/Mainenti Reverb.vst3" "VST3 (Sistema)"
remove_quarantine "$HOME/Library/Audio/Plug-Ins/VST3/Mainenti Reverb.vst3" "VST3 (Utente)"

# Audio Unit
remove_quarantine "/Library/Audio/Plug-Ins/Components/Mainenti Reverb.component" "Audio Unit (Sistema)"
remove_quarantine "$HOME/Library/Audio/Plug-Ins/Components/Mainenti Reverb.component" "Audio Unit (Utente)"

# Standalone
remove_quarantine "/Applications/Mainenti Reverb.app" "Standalone (Applicazioni)"
remove_quarantine "$HOME/Applications/Mainenti Reverb.app" "Standalone (Utente)"

# Cerca nella cartella corrente
if [ -d "Mainenti Reverb.vst3" ]; then
    remove_quarantine "./Mainenti Reverb.vst3" "VST3 (Cartella corrente)"
fi

if [ -d "Mainenti Reverb.component" ]; then
    remove_quarantine "./Mainenti Reverb.component" "AU (Cartella corrente)"
fi

if [ -d "Mainenti Reverb.app" ]; then
    remove_quarantine "./Mainenti Reverb.app" "Standalone (Cartella corrente)"
fi

echo ""
echo "=================================="
echo "Operazione completata!"
echo ""
echo "Ora puoi:"
echo "1. Riavviare la tua DAW"
echo "2. Ricaricare la lista dei plugin"
echo "3. Usare Mainenti Reverb"
echo "=================================="
