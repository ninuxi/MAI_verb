# Installazione su Linux - MAI_verb

## Formati Disponibili
- **VST3**: Da usare in qualsiasi DAW compatibile VST3 (Reaper, Ardour, Bitwig, ecc.)
- **Standalone**: Applicazione indipendente

## Posizioni di Installazione

### VST3 (Posizione standard)
```bash
~/.vst3/
```

### VST3 (Sistema - richiede sudo)
```bash
/usr/lib/vst3/
```
oppure
```bash
/usr/local/lib/vst3/
```

### Standalone
```bash
~/.local/bin/
```
oppure
```bash
/usr/local/bin/
```

## Istruzioni per l'Installazione

### Installazione Rapida (Utente)

```bash
# Crea la directory VST3 se non esiste
mkdir -p ~/.vst3

# Copia il plugin VST3
cp -r "MAI_verb.vst3" ~/.vst3/

# Per lo standalone (opzionale)
mkdir -p ~/.local/bin
cp "MAI_verb" ~/.local/bin/
chmod +x ~/.local/bin/"MAI_verb"
```

### Installazione Sistema (richiede sudo)

```bash
# Per VST3
sudo mkdir -p /usr/local/lib/vst3
sudo cp -r "MAI_verb.vst3" /usr/local/lib/vst3/

# Per Standalone
sudo cp "MAI_verb" /usr/local/bin/
sudo chmod +x /usr/local/bin/"MAI_verb"
```

### Verifica Installazione

```bash
# Controlla se il plugin è presente
ls -la ~/.vst3/
# oppure
ls -la /usr/local/lib/vst3/

# Testa lo standalone
"~/.local/bin/MAI_verb"
# oppure
/usr/local/bin/"MAI_verb"
```

## Compilazione su Linux

### Requisiti

#### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake git pkg-config \
    libasound2-dev libjack-jackd2-dev \
    libfreetype6-dev libx11-dev libxrandr-dev libxinerama-dev \
    libxcursor-dev libgl1-mesa-dev libwebkit2gtk-4.0-dev
```

#### Fedora/RHEL:
```bash
sudo dnf install gcc-c++ cmake git pkgconfig \
    alsa-lib-devel jack-audio-connection-kit-devel \
    freetype-devel libX11-devel libXrandr-devel libXinerama-devel \
    libXcursor-devel mesa-libGL-devel webkit2gtk3-devel
```

#### Arch Linux:
```bash
sudo pacman -S base-devel cmake git alsa-lib jack2 \
    freetype2 libx11 libxrandr libxinerama libxcursor mesa webkit2gtk
```

### Passi di Compilazione

1. **Clona il repository:**
   ```bash
   git clone [url-del-progetto]
   cd make_plugin_riverberi/BricastiM7_Clone
   ```

2. **Prepara la build:**
   ```bash
   mkdir build
   cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   ```

3. **Compila:**
   ```bash
   make -j$(nproc)
   ```

4. **I file compilati saranno in:**
   ```
   build/BricastiM7_artefacts/VST3/MAI_verb.vst3
   build/BricastiM7_artefacts/Standalone/MAI_verb
   ```

5. **Installa automaticamente:**
   ```bash
   # VST3
   cp -r build/BricastiM7_artefacts/VST3/"MAI_verb.vst3" ~/.vst3/
   
   # Standalone
   cp build/BricastiM7_artefacts/Standalone/"MAI_verb" ~/.local/bin/
   chmod +x ~/.local/bin/"MAI_verb"
   ```

## Configurazione DAW

### Reaper
1. Options → Preferences → Plug-ins → VST
2. Aggiungi il percorso: `~/.vst3` o `/usr/local/lib/vst3`
3. Click "Re-scan" o "Clear cache/re-scan"

### Bitwig Studio
1. Settings → Locations → VST3 Plug-ins
2. Aggiungi la cartella e scannerizza

### Ardour
1. Edit → Preferences → Plugins
2. Aggiungi il percorso VST3
3. Riavvia Ardour

### LMMS
1. Edit → Settings → Paths
2. VST plugin folder → Aggiungi `~/.vst3`

## Risoluzione Problemi

### Plugin non caricato - Dipendenze mancanti

Controlla le dipendenze mancanti:
```bash
ldd ~/.vst3/"MAI_verb.vst3/Contents/x86_64-linux/MAI_verb.so"
```

Se mancano librerie, installale:
```bash
# Ubuntu/Debian
sudo apt install libc6 libgcc1 libstdc++6

# Fedora
sudo dnf install glibc libgcc libstdc++
```

### Permessi Negati

```bash
chmod -R 755 ~/.vst3/"MAI_verb.vst3"
```

### JACK non funziona

Verifica che JACK sia in esecuzione:
```bash
jack_control status
# Se non è attivo:
jack_control start
```

### Problemi con lo Standalone

```bash
# Controlla se è eseguibile
chmod +x ~/.local/bin/"MAI_verb"

# Esegui con debug per vedere errori
~/.local/bin/"MAI_verb" --verbose
```

### Audio non funziona (Standalone)

Il plugin usa ALSA o JACK. Se hai problemi:
1. Installa PulseAudio Bridge: `sudo apt install pulseaudio-module-jack`
2. Oppure usa JACK invece di PulseAudio
3. Oppure compila con supporto PulseAudio diretto

## Note

- Su Linux, i plugin VST3 sono cartelle (bundle) come su macOS
- La struttura interna è: `MAI_verb.vst3/Contents/x86_64-linux/*.so`
- Per ARM64: `aarch64-linux/` invece di `x86_64-linux/`
- Lo standalone richiede un sistema audio configurato (ALSA/JACK/PulseAudio)

## Sistemi Testati

- ✅ Ubuntu 20.04, 22.04, 24.04
- ✅ Debian 11, 12
- ✅ Fedora 38, 39
- ✅ Arch Linux (rolling)
- ⚠️ Altri: dovrebbero funzionare ma non testati

## Distribuzione del Plugin

Se vuoi distribuire il plugin compilato per Linux:
1. Compila su una distribuzione stabile (es. Ubuntu 20.04)
2. Includi tutte le dipendenze o usa AppImage/Flatpak
3. Fornisci istruzioni chiare per le dipendenze richieste
