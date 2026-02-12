# Installazione su Windows - MAI_verb

## Formati Disponibili
- **VST3**: Da usare in qualsiasi DAW (Ableton, FL Studio, Reaper, ecc.)
- **Standalone**: Applicazione indipendente

Nota: il formato **CLAP** non e' attualmente supportato dal progetto. Il formato **LV2** e' pensato per Linux.

## Posizioni di Installazione

### VST3 (Consigliato)
```
C:\Program Files\Common Files\VST3\
```

### Standalone
```
C:\Program Files\MAI_verb\
```

Oppure nella cartella del Desktop o dove preferisci.

## Istruzioni per l'Installazione

### Metodo 1: Installazione Manuale

1. **Per il VST3:**
   - Copia `MAI_verb.vst3` in:
     ```
     C:\Program Files\Common Files\VST3\
     ```
   - Potrebbero essere richiesti permessi di amministratore

2. **Per lo Standalone:**
   - Copia l'applicazione `MAI_verb.exe` dove preferisci
   - Crea un collegamento sul Desktop se vuoi

3. **Riavvia la tua DAW** e ricarica la lista dei plugin

### Metodo 2: Installazione Alternativa (Utente)

Se non hai permessi di amministratore, usa queste posizioni:

#### VST3:
```
C:\Users\[TuoNome]\AppData\Local\Programs\Common\VST3\
```

#### Standalone:
```
C:\Users\[TuoNome]\AppData\Local\Programs\MAI_verb\
```

## Compilazione su Windows

Se vuoi compilare il plugin da solo:

### Requisiti:
- Visual Studio 2019 o superiore (con C++ Desktop Development)
- CMake 3.22 o superiore
- Git

### Passi:

1. **Clona il repository:**
   ```cmd
   git clone [url-del-progetto]
   cd make_plugin_riverberi\BricastiM7_Clone
   ```

2. **Prepara la build:**
   ```cmd
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022"
   ```

3. **Compila:**
   ```cmd
   cmake --build . --config Release
   ```

4. **I file compilati saranno in:**
   ```
   build\BricastiM7_artefacts\Release\VST3\MAI_verb.vst3
   build\BricastiM7_artefacts\Release\Standalone\MAI_verb.exe
   ```

## Verifica dell'Installazione

1. Apri la tua DAW
2. Vai nelle impostazioni dei plugin e assicurati che la cartella VST3 sia scansionata:
   - **Ableton Live**: Preferences → Plug-ins → VST3 System Folders
   - **FL Studio**: Options → File Settings → VST plugins folder
   - **Reaper**: Options → Preferences → Plug-ins → VST → VST3

3. Ricarica/Riscannerizza i plugin
4. Cerca "MAI_verb" nella lista

## Risoluzione Problemi

### Plugin non appare nella DAW

1. **Verifica il percorso:** Assicurati di aver copiato il file nella posizione corretta
2. **Riscannerizza:** Forza la DAW a ricaricare la lista dei plugin
3. **Controlla i log:** Alcune DAW mostrano errori nel caricamento dei plugin
4. **Permessi:** Assicurati di avere i permessi per accedere alla cartella

### Visual C++ Runtime Error

Se appare un errore su `VCRUNTIME140.dll` o simili:
1. Scarica e installa [Microsoft Visual C++ Redistributable](https://learn.microsoft.com/cpp/windows/latest-supported-vc-redist)
2. Installa sia la versione x64 che x86

### Windows Defender / SmartScreen

Windows potrebbe bloccare il file perché non è firmato:
1. Click destro sul file → Proprietà
2. Spunta "Sblocca" in basso → Applica
3. Oppure: Click "Maggiori informazioni" → "Esegui comunque"

## Note

- I plugin VST3 sono cartelle (bundle) anche su Windows
- Non serve il formato VST2 (deprecato)
- Lo standalone può essere eseguito direttamente senza DAW
