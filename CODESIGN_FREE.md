# 🔓 Code Signing Gratuito per Plugin Open Source

## 🎯 Obiettivo
Distribuire plugin VST3/AU open source senza pagare Apple Developer (€99/anno), permettendo agli utenti di installarli facilmente su macOS.

## ⚠️ Importante
Questo metodo usa **ad-hoc signing** (firma locale gratuita) che:
- ✅ **NON richiede** account Apple Developer
- ✅ **Funziona** per distribuire plugin open source
- ✅ È **completamente gratuito**
- ❌ **NON permette** distribuzione su App Store
- ❌ **NON bypassa** automaticamente Gatekeeper (richiede azione utente)

---

## 🛠️ Per Te (Developer): Come Firmare i Plugin

### 1. Build del Plugin

```bash
cd BricastiM7_Clone
./build_m7.sh
```

### 2. Firma Ad-Hoc (Gratuita)

```bash
#!/bin/bash
# Script di firma ad-hoc per plugin

PLUGIN_VST3="build/BricastiM7_artefacts/Release/VST3/MAI_verb.vst3"
PLUGIN_AU="build/BricastiM7_artefacts/Release/AU/MAI_verb.component"

echo "🔐 Firma ad-hoc dei plugin..."

# Firma VST3
if [ -d "$PLUGIN_VST3" ]; then
    codesign --deep --force --sign - \
        --options runtime \
        --identifier "com.aiforlive.MAI_verb" \
        "$PLUGIN_VST3"
    echo "✅ VST3 firmato"
fi

# Firma AU
if [ -d "$PLUGIN_AU" ]; then
    codesign --deep --force --sign - \
        --options runtime \
        --identifier "com.aiforlive.MAI_verb.component" \
        "$PLUGIN_AU"
    echo "✅ AU firmato"
fi

echo "🎉 Firma completata!"
```

Salva come `sign_plugins.sh`, rendilo eseguibile:

```bash
chmod +x sign_plugins.sh
./sign_plugins.sh
```

### 3. Verifica Firma

```bash
# Verifica VST3
codesign -dv --verbose=4 build/BricastiM7_artefacts/Release/VST3/MAI_verb.vst3

# Verifica AU
codesign -dv --verbose=4 build/BricastiM7_artefacts/Release/AU/MAI_verb.component
```

Dovresti vedere: `Signature=adhoc` (OK!)

### 4. Crea Release ZIP

```bash
#!/bin/bash
# Crea pacchetto per distribuzione

VERSION="v0.1.0"
RELEASE_NAME="MAI_verb_${VERSION}_macOS"

mkdir -p "releases/$RELEASE_NAME"

# Copia plugin firmati
cp -r build/BricastiM7_artefacts/Release/VST3/MAI_verb.vst3 "releases/$RELEASE_NAME/"
cp -r build/BricastiM7_artefacts/Release/AU/MAI_verb.component "releases/$RELEASE_NAME/"

# Copia istruzioni
cp INSTALL_INSTRUCTIONS.md "releases/$RELEASE_NAME/README.txt"

# Crea ZIP
cd releases
zip -r "${RELEASE_NAME}.zip" "$RELEASE_NAME"

echo "✅ Release creata: releases/${RELEASE_NAME}.zip"
```

---

## 👥 Per Gli Utenti: Come Installare Plugin Non-Firmati

### Metodo 1: Rimozione Quarantena (Consigliato)

Dopo aver scaricato e estratto il plugin, **PRIMA** di copiarlo:

```bash
# Per VST3
xattr -cr MAI_verb.vst3

# Per AU
xattr -cr MAI_verb.component
```

Poi copia normalmente:

```bash
# VST3
cp -r MAI_verb.vst3 ~/Library/Audio/Plug-Ins/VST3/

# AU
cp -r MAI_verb.component ~/Library/Audio/Plug-Ins/Components/
```

### Metodo 2: Dopo Installazione

Se hai già copiato il plugin e la DAW lo blocca:

```bash
# Rimuovi quarantena VST3
xattr -cr ~/Library/Audio/Plug-Ins/VST3/MAI_verb.vst3

# Rimuovi quarantena AU
xattr -cr ~/Library/Audio/Plug-Ins/Components/MAI_verb.component

# Riavvia la DAW
```

### Metodo 3: Bypass Gatekeeper (Non Consigliato)

Solo se i metodi precedenti non funzionano:

1. Sistema > Privacy e Sicurezza
2. Cerca il messaggio sul plugin bloccato
3. Clicca "Apri comunque"

---

## 📦 Template README per GitHub Release

Includi questo nel README del tuo repository:

```markdown
## 🔓 Installazione su macOS

Questo plugin è **firmato localmente** (ad-hoc) e NON ha un certificato Apple Developer.

### Rimozione Quarantena (OBBLIGATORIO)

Dopo aver scaricato il ZIP, esegui:

\`\`\`bash
# 1. Estrai il ZIP
unzip MAI_verb_v0.1.0_macOS.zip
cd MAI_verb_v0.1.0_macOS

# 2. Rimuovi attributi di quarantena
xattr -cr MAI_verb.vst3
xattr -cr MAI_verb.component

# 3. Copia nelle directory dei plugin
cp -r MAI_verb.vst3 ~/Library/Audio/Plug-Ins/VST3/
cp -r MAI_verb.component ~/Library/Audio/Plug-Ins/Components/

# 4. Riavvia la tua DAW
\`\`\`

### Problema: "Il plugin non può essere aperto"

Se la DAW blocca ancora il plugin:

\`\`\`bash
# Rimuovi quarantena dalle directory finali
xattr -cr ~/Library/Audio/Plug-Ins/VST3/MAI_verb.vst3
xattr -cr ~/Library/Audio/Plug-Ins/Components/MAI_verb.component
\`\`\`

## ✅ Plugin Verificato

- 🔐 Firmato con ad-hoc signature
- ✅ Codice open source su GitHub
- 👤 Autore: Mainenti @ aiforlive
\`\`\`

---

## 🚀 Script Completo per Automated Release

Salva come `prepare_release.sh`:

```bash
#!/bin/bash
set -e

VERSION="${1:-v0.1.0}"
RELEASE_NAME="MAI_verb_${VERSION}_macOS"

echo "🔧 Building plugin..."
cd BricastiM7_Clone
./build_m7.sh

echo "🔐 Signing plugins (ad-hoc)..."
codesign --deep --force --sign - \
    --options runtime \
    build/BricastiM7_artefacts/Release/VST3/MAI_verb.vst3

codesign --deep --force --sign - \
    --options runtime \
    build/BricastiM7_artefacts/Release/AU/MAI_verb.component

echo "📦 Creating release package..."
cd ..
mkdir -p "releases/$RELEASE_NAME"

cp -r "BricastiM7_Clone/build/BricastiM7_artefacts/Release/VST3/MAI_verb.vst3" \
    "releases/$RELEASE_NAME/"

cp -r "BricastiM7_Clone/build/BricastiM7_artefacts/Release/AU/MAI_verb.component" \
    "releases/$RELEASE_NAME/"

# Crea README per utenti
cat > "releases/$RELEASE_NAME/README.txt" << 'EOF'
MAI_verb by Mainenti @ aiforlive
Professional Algorithmic Reverb - Open Source

INSTALLAZIONE macOS
===================

IMPORTANTE: Esegui PRIMA di copiare i plugin:

    xattr -cr MAI_verb.vst3
    xattr -cr MAI_verb.component

Poi installa:

    cp -r MAI_verb.vst3 ~/Library/Audio/Plug-Ins/VST3/
    cp -r MAI_verb.component ~/Library/Audio/Plug-Ins/Components/

Riavvia la tua DAW.

Per supporto: https://github.com/ninuxi/MAI_verb
EOF

cd releases
zip -r "${RELEASE_NAME}.zip" "$RELEASE_NAME"

echo "✅ Release pronta: releases/${RELEASE_NAME}.zip"
echo "📤 Caricala su GitHub Releases"
```

Utilizzo:

```bash
chmod +x prepare_release.sh
./prepare_release.sh v0.1.0
```

---

## 📝 Note Legali

- La firma ad-hoc è **legale e legittima**
- Apple la supporta ufficialmente per sviluppo locale
- NON viola alcun termine di servizio
- È il metodo standard per plugin open source gratuiti

## 🔗 Link Utili

- [Apple Codesign Documentation](https://developer.apple.com/documentation/security/notarizing_macos_software_before_distribution)
- [JUCE Forum - Distributing Plugins](https://forum.juce.com)
