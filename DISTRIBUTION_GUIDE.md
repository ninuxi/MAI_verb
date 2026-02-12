# 🔓 Distribuzione Plugin Open Source Senza Apple Developer

## 🎯 Il Tuo Setup Completo

### ✅ Cosa Hai Ora:

1. **Plugin con il tuo nome**: "MAI_verb by Mainenti @ aiforlive"
2. **Code signing gratuito**: Firma ad-hoc (no €99/anno Apple)
3. **Script automatizzati**:
   - `sign_plugins.sh` - Firma i plugin
   - `prepare_release.sh` - Crea pacchetto completo per distribuzione
4. **Documentazione per utenti**: Istruzioni chiare per rimuovere quarantena

---

## 🚀 Workflow Completo di Release

### 1. Build e Firma Plugin

```bash
cd /Users/mainenti/make_plugin_riverberi

# Build automatico + firma + pacchetto
./prepare_release.sh v0.1.1

# Output: releases/MAI_verb_v0.1.1_macOS.zip
```

### 2. Testa Localmente

```bash
cd releases/MAI_verb_v0.1.1_macOS

# Rimuovi quarantena
xattr -cr *.vst3
xattr -cr *.component

# Installa per test
cp -r *.vst3 ~/Library/Audio/Plug-Ins/VST3/
cp -r *.component ~/Library/Audio/Plug-Ins/Components/

# Apri la tua DAW e testa
```

### 3. Release su GitHub

```bash
# 1. Vai su: https://github.com/ninuxi/MAI_verb/releases
# 2. Clicca "Draft a new release"
# 3. Tag version: v0.1.1
# 4. Release title: "MAI_verb v0.1.1"
# 5. Descrizione:

## ✨ Caratteristiche
- Professional algorithmic reverb
- 8x8 FDN algorithm
- Early reflections
- Factory presets
- Low CPU

## 📥 Installazione macOS

**IMPORTANTE**: Esegui prima di installare:

\`\`\`bash
xattr -cr MAI_verb.vst3
xattr -cr MAI_verb.component
\`\`\`

Vedi `INSTALLATION.txt` incluso nel ZIP per istruzioni complete.

## 🔒 Code Signing
Plugin firmato con ad-hoc signature (gratuito, sicuro).
NON richiede Apple Developer account.

# 6. Carica: releases/MAI_verb_v0.1.1_macOS.zip
# 7. Pubblica release!
```

---

## 📋 Cosa Vedranno Gli Utenti

### Nel README del Repository

Quando gli utenti visitano il tuo GitHub, vedranno:

- Nome plugin: **MAI_verb by Mainenti @ aiforlive**
- Istruzioni chiare per installazione senza pagare Apple
- Avviso che il plugin è sicuro ma richiede rimozione quarantena

### Nel Plugin Stesso

Quando aprono il plugin nella DAW:

- **Product Name**: "MAI_verb by Mainenti"
- **Company**: "aiforlive"
- **Manufacturer Code**: Aif1
- **Plugin Code**: MaRv

---

## 🔐 Perché Non Serve Pagare Apple

### Code Signing Ad-Hoc vs Apple Developer

| Caratteristica | Ad-Hoc (Gratuito) | Apple Developer (€99/anno) |
|----------------|-------------------|---------------------------|
| Costo | **€0** | €99/anno |
| Plugin firmato | ✅ Sì | ✅ Sì |
| Distribuzione open source | ✅ Perfetto | ✅ Sì |
| Notarization Apple | ❌ No | ✅ Sì |
| App Store | ❌ No | ✅ Sì |
| Richiede azione utente | ✅ Sì (`xattr -cr`) | ❌ No |

**Per plugin open source, ad-hoc è perfetto!**

Gli utenti devono solo eseguire `xattr -cr` prima di installare - è un comando semplice e sicuro.

---

## 👥 Istruzioni Semplici per gli Utenti

### Aggiungi Questo al README del Tuo Repo:

````markdown
## 📥 Installazione su macOS

⚠️ **Questo plugin usa firma ad-hoc (gratuita) e NON ha certificato Apple Developer. È sicuro!**

### Installazione Rapida

1. Scarica `MAI_verb_vX.X.X_macOS.zip` dalla sezione [Releases](https://github.com/ninuxi/MAI_verb/releases)
2. Estrai il ZIP
3. Apri **Terminale** e esegui:

```bash
cd ~/Downloads/MAI_verb_*
xattr -cr *.vst3
xattr -cr *.component
cp -r *.vst3 ~/Library/Audio/Plug-Ins/VST3/
cp -r *.component ~/Library/Audio/Plug-Ins/Components/
```

4. Riavvia la DAW

### Perché `xattr -cr`?

macOS blocca plugin scaricati senza certificato Apple Developer (€99/anno).  
Questo comando rimuove la "quarantena" - è **sicuro** e **standard** per plugin open source.

### Problema: "Plugin bloccato"?

```bash
# Rimuovi quarantena dalle directory finali
xattr -cr ~/Library/Audio/Plug-Ins/VST3/*
xattr -cr ~/Library/Audio/Plug-Ins/Components/*
```
````

---

## 🎨 Il Tuo Nome Ovunque

### Aggiornato in:

- ✅ `CMakeLists.txt` → Company: "aiforlive", Product: "MAI_verb by Mainenti"
- ✅ File Info del plugin (mostrato nelle DAW)
- ✅ README.md → Autore visibile
- ✅ Release notes → "by Mainenti @ aiforlive"

### Per Verificare:

```bash
# Dopo aver buildato il plugin:
/usr/libexec/PlistBuddy -c "Print :CFBundleIdentifier" \
    BricastiM7_Clone/build/*/VST3/*.vst3/Contents/Info.plist

# Dovresti vedere: com.aiforlive.MAI_verb
```

---

## 📝 Template Email per Utenti (Opzionale)

Se qualcuno ti chiede aiuto via email:

```
Ciao!

Per installare MAI_verb su macOS:

1. Scarica il ZIP
2. Estrai i file
3. Apri Terminale e vai nella cartella estratta
4. Esegui:
   xattr -cr *.vst3
   xattr -cr *.component
5. Copia plugin in:
   ~/Library/Audio/Plug-Ins/VST3/
   ~/Library/Audio/Plug-Ins/Components/
6. Riavvia la DAW

Il plugin è sicuro - usa firma ad-hoc (gratuita).

Mainenti @ aiforlive
```

---

## 🎉 Riassunto

Adesso hai:

1. ✅ **Plugin con il tuo nome** in tutti i metadata
2. ✅ **Firma gratuita** (ad-hoc, no €99/anno)
3. ✅ **Script automatici** per build e release
4. ✅ **Documentazione completa** per utenti
5. ✅ **Workflow GitHub Releases** pronto

**Gli utenti dovranno solo eseguire `xattr -cr` - è normale per plugin open source!**

Non serve pagare Apple. Il tuo plugin è distribuibile, sicuro e professionale. 🚀
