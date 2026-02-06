#!/bin/bash

# Script per inizializzare repository GitHub MAI_verb
# Questo script prepara il repository locale per il push su GitHub

echo "════════════════════════════════════════"
echo "   MAI_verb - GitHub Setup"
echo "════════════════════════════════════════"
echo ""

PROJECT_DIR="/Users/mainenti/make_plugin_riverberi"
cd "$PROJECT_DIR"

# Colori
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${BLUE}📋 Preparazione repository...${NC}"
echo ""

# Controlla se git è già inizializzato
if [ -d ".git" ]; then
    echo -e "${YELLOW}⚠  Repository git già inizializzato${NC}"
    echo "Vuoi continuare? (y/n)"
    read -r response
    if [[ ! "$response" =~ ^[Yy]$ ]]; then
        echo "Operazione annullata."
        exit 0
    fi
else
    # Inizializza git
    git init
    echo -e "${GREEN}✓${NC} Repository git inizializzato"
fi

# Assicurati che sia sulla branch main
git branch -M main 2>/dev/null
echo -e "${GREEN}✓${NC} Branch main impostato"

# Aggiungi tutti i file
git add .
echo -e "${GREEN}✓${NC} File aggiunti al commit"

# Commit iniziale
git commit -m "Initial commit - MAI_verb v0.1

- Professional algorithmic reverb plugin
- 8x8 FDN reverb algorithm
- Early reflections simulation
- Modulation and shimmer effects
- Cross-platform support (macOS, Windows, Linux)
- VST3, AU (macOS), and Standalone formats" 2>/dev/null

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓${NC} Commit iniziale creato"
else
    echo -e "${YELLOW}⚠${NC}  Nessuna modifica da committare o commit già esistente"
fi

echo ""
echo "════════════════════════════════════════"
echo -e "${GREEN}✓ Repository locale pronto!${NC}"
echo "════════════════════════════════════════"
echo ""
echo -e "${YELLOW}📝 PROSSIMI PASSI MANUALI:${NC}"
echo ""
echo "1️⃣  Crea il repository su GitHub:"
echo "   Vai a: https://github.com/new"
echo "   - Repository name: ${GREEN}MAI_verb${NC}"
echo "   - Description: Professional Algorithmic Reverb Plugin"
echo "   - Visibilità: Public (o Private)"
echo "   - NON inizializzare con README"
echo ""
echo "2️⃣  Collega il repository:"
echo "   ${BLUE}git remote add origin https://github.com/[tuo-username]/MAI_verb.git${NC}"
echo ""
echo "3️⃣  Push su GitHub:"
echo "   ${BLUE}git push -u origin main${NC}"
echo ""
echo "4️⃣  Crea la Release v0.1:"
echo "   - Vai a: https://github.com/[tuo-username]/MAI_verb/releases/new"
echo "   - Tag version: ${GREEN}v0.1${NC}"
echo "   - Release title: ${GREEN}MAI_verb v0.1 - Initial Release${NC}"
echo "   - Description: Copia da ~/Desktop/MAI_verb_Release_v0.1/RELEASE_NOTES.md"
echo "   - Carica file: ${GREEN}MAI_verb_v0.1_macOS.zip${NC}"
echo "   - Pubblica release"
echo ""
echo "════════════════════════════════════════"
echo ""
echo "💡 Oppure usa GitHub CLI (se installato):"
echo ""
echo "   ${BLUE}# Crea repository${NC}"
echo "   gh repo create MAI_verb --public --source=. --remote=origin"
echo ""
echo "   ${BLUE}# Push${NC}"
echo "   git push -u origin main"
echo ""
echo "   ${BLUE}# Crea release${NC}"
echo "   gh release create v0.1 \\"
echo "     --title \"MAI_verb v0.1 - Initial Release\" \\"
echo "     --notes-file ~/Desktop/MAI_verb_Release_v0.1/RELEASE_NOTES.md \\"
echo "     ~/Desktop/MAI_verb_Release_v0.1/MAI_verb_v0.1_macOS.zip"
echo ""
echo "════════════════════════════════════════"
echo ""
echo "📦 File release disponibile:"
echo "   ${GREEN}~/Desktop/MAI_verb_Release_v0.1/MAI_verb_v0.1_macOS.zip${NC}"
echo ""
