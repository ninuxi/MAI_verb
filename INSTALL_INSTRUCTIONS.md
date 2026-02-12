# Istruzioni per l'Installazione - MAI_verb

## 🖥️ Scegli il tuo Sistema Operativo

- **macOS** → Continua a leggere questa guida
- **Windows** → Leggi [INSTALL_WINDOWS.md](INSTALL_WINDOWS.md)
- **Linux** → Leggi [INSTALL_LINUX.md](INSTALL_LINUX.md)

---

## Installazione su macOS

### Formati Disponibili
- **VST3**: Per qualsiasi DAW compatibile
- **AU (Audio Unit)**: Per Logic Pro, GarageBand, ecc.
- **Standalone**: Applicazione indipendente

## Problema Gatekeeper su macOS

Questo plugin non è firmato da Apple, quindi macOS Gatekeeper lo metterà in quarantena.

## Soluzione

### Metodo 1: Script Automatico (Consigliato)

1. Apri il **Terminale** (Applicazioni > Utility > Terminale)
2. Naviga nella cartella dove hai scaricato il plugin
3. Esegui questo comando:

```bash
chmod +x remove_quarantine.sh
./remove_quarantine.sh
```

### Metodo 2: Comando Manuale (Consigliato)

Apri il Terminale e esegui uno di questi comandi a seconda del formato che usi:

#### Per VST3:
```bash
sudo xattr -rd com.apple.quarantine "/Library/Audio/Plug-Ins/VST3/MAI_verb.vst3"
```

#### Per AU (Audio Unit):
```bash
sudo xattr -rd com.apple.quarantine "/Library/Audio/Plug-Ins/Components/MAI_verb.component"
```

#### Per l'app Standalone:
```bash
sudo xattr -rd com.apple.quarantine "/Applications/MAI_verb.app"
```

#### Se il plugin è nella cartella Downloads (prima di installarlo):
```bash
xattr -rd com.apple.quarantine ~/Downloads/MAI_verb.vst3
```

**Cosa fa questo comando:**
- `sudo` = esegue con permessi amministratore (ti chiederà la password)
- `xattr` = gestisce gli attributi estesi dei file
- `-rd` = rimuove ricorsivamente l'attributo specificato
- `com.apple.quarantine` = l'attributo specifico che blocca il plugin

**Alternativa senza sudo (rimuove tutti gli attributi):**
```bash
xattr -cr "/Library/Audio/Plug-Ins/VST3/MAI_verb.vst3"
```

### Metodo 3: Tramite Finder (Se il sistema blocca l'apertura)

1. Vai su **Preferenze di Sistema** > **Privacy e Sicurezza**
2. Scorri in basso fino alla sezione "Sicurezza"
3. Dovresti vedere un messaggio riguardo il plugin bloccato
4. Clicca su **"Apri comunque"** o **"Consenti"**

## Verifica dell'Installazione

Dopo aver rimosso la quarantena, apri la tua DAW (Ableton, Logic, ecc.) e verifica che il plugin appaia nella lista.

## Note

- Questi comandi sono sicuri e rimuovono solo l'attributo di quarantena
- Il flag `-c` rimuove tutti gli attributi estesi
- Il flag `-r` opera ricorsivamente su tutti i file del bundle
