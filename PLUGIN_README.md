# Mainenti Reverb - Plugin Audio Professionale

Un reverb algoritmico di alta qualità ispirato ai processori hardware professionali.

## 🌍 Supporto Multi-Piattaforma

Mainenti Reverb è disponibile per tutti i principali sistemi operativi:

| Sistema | VST3 | AU | Standalone |
|---------|------|-----|------------|
| **macOS** | ✅ | ✅ | ✅ |
| **Windows** | ✅ | ❌ | ✅ |
| **Linux** | ✅ | ❌ | ✅ |

*AU (Audio Unit) è disponibile solo su macOS*

## 📥 Installazione

Scegli la guida per il tuo sistema operativo:

- 🍎 **[macOS](INSTALL_INSTRUCTIONS.md)** - Include soluzione per Gatekeeper
- 🪟 **[Windows](INSTALL_WINDOWS.md)** - VST3 e Standalone
- 🐧 **[Linux](INSTALL_LINUX.md)** - Compilazione e installazione

## 🎛️ Caratteristiche

- **Algoritmo FDN 8x8** per texture naturali e complesse
- **Early Reflections** realistiche e personalizzabili
- **Modulazione** per chorus ed effetti shimmer
- **EQ Integrato** pre e post-riverbero
- **Preset Factory** ispirati ai classici hardware
- **Basso consumo CPU** grazie all'ottimizzazione JUCE
- **Interface Intuitiva** con controlli chiari

## 🎚️ Parametri Principali

### Sezione Principale
- **Mix (Dry/Wet)**: Bilanciamento tra segnale originale e reverbero
- **Decay Time**: Durata del riverbero (0.1s - 30s)
- **Pre-Delay**: Ritardo prima dell'onset del riverbero

### Sezione Size & Diffusion
- **Room Size**: Dimensione dello spazio simulato
- **Diffusion**: Densità e scattering delle riflessioni

### Early Reflections
- **ER Level**: Volume delle prime riflessioni
- **ER Pattern**: Caratteristiche della stanza (piccola, media, grande, hall)

### Modulazione
- **Mod Rate**: Velocità della modulazione
- **Mod Depth**: Intensità della modulazione
- **Shimmer**: Effetto "shimmer" con pitch shifting

### EQ
- **Low Cut**: Filtro passa-alto
- **High Cut**: Filtro passa-basso
- **Pre/Post**: Posizione dell'EQ nella catena

## 🎵 Utilizzo

### DAW Supportate

**macOS:**
- Logic Pro / Logic Pro X ✅
- Ableton Live ✅
- FL Studio ✅
- Reaper ✅
- Studio One ✅
- Cubase / Nuendo ✅
- Pro Tools (VST3) ✅

**Windows:**
- Ableton Live ✅
- FL Studio ✅
- Reaper ✅
- Studio One ✅
- Cubase / Nuendo ✅
- Bitwig Studio ✅

**Linux:**
- Reaper ✅
- Bitwig Studio ✅
- Ardour ✅
- LMMS ✅
- Tracktion Waveform ✅

### Modalità Standalone

Il plugin include anche una versione standalone che può essere eseguita indipendentemente da una DAW:
- Ideale per test e sperimentazione
- Supporta input/output audio dal sistema
- Tutti i parametri e preset disponibili

## 🔧 Compilazione dal Sorgente

### Requisiti Generali
- CMake 3.22+
- Compilatore C++17 (GCC, Clang, MSVC)
- JUCE Framework (incluso nel progetto)

### Quick Start
```bash
# Clona il repository
git clone [url-repository]
cd make_plugin_riverberi/BricastiM7_Clone

# Build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

Per istruzioni dettagliate per ogni OS:
- [Compilazione su macOS](INSTALL_INSTRUCTIONS.md#compilazione-dal-sorgente)
- [Compilazione su Windows](INSTALL_WINDOWS.md#compilazione-su-windows)
- [Compilazione su Linux](INSTALL_LINUX.md#compilazione-su-linux)

## 📦 Struttura del Progetto

```
make_plugin_riverberi/
├── BricastiM7_Clone/          # Progetto principale
│   ├── Source/                 # Codice sorgente
│   │   ├── PluginProcessor.cpp # Elaborazione audio
│   │   ├── PluginEditor.cpp    # Interface grafica
│   │   └── DSP/                # Algoritmi DSP
│   ├── CMakeLists.txt          # Configurazione build
│   └── BricastiM7.jucer        # Progetto Projucer
├── JUCE/                       # Framework JUCE
├── INSTALL_INSTRUCTIONS.md     # Guida macOS
├── INSTALL_WINDOWS.md          # Guida Windows
└── INSTALL_LINUX.md            # Guida Linux
```

## 🐛 Risoluzione Problemi

### macOS: "Plugin non può essere aperto" (Gatekeeper)
→ Leggi [INSTALL_INSTRUCTIONS.md](INSTALL_INSTRUCTIONS.md)

### Windows: "VCRUNTIME140.dll mancante"
→ Installa [Visual C++ Redistributable](https://learn.microsoft.com/cpp/windows/latest-supported-vc-redist)

### Linux: "Plugin non caricato"
→ Controlla dipendenze con `ldd` - leggi [INSTALL_LINUX.md](INSTALL_LINUX.md)

### Plugin non appare nella DAW
1. Verifica il percorso di installazione
2. Riscannerizza i plugin nella DAW
3. Controlla i log della DAW per errori

## 📄 Licenza

[Specifica la tua licenza qui]

## 👨‍💻 Autore

**Mainenti** - Sviluppo e Design

## 🙏 Crediti

- **JUCE Framework** per l'infrastruttura audio e GUI
- Ispirato dai reverb hardware professionali classici

## 📮 Contatti & Supporto

[Aggiungi qui i tuoi contatti o link al repository per issue/supporto]

---

**Versione**: 1.0.0  
**Ultima Aggiornamento**: Febbraio 2026  
**Compatibilità**: macOS 10.13+, Windows 10+, Linux (moderne distro)
