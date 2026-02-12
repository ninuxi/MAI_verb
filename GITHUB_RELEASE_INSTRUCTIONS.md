# Come Pubblicare la Release su GitHub

## Passo 1: Commit e Push delle modifiche

```bash
# Aggiungi i file modificati
git add README.md INSTALL_LINUX.md CMakeLists.txt build.sh
git add prepare_release_linux.sh RELEASE_NOTES_v0.1.1.md
git add BricastiM7_Clone/CMakeLists.txt
git add BricastiM7_Clone_New/CMakeLists.txt
git add BricastiM7_Fixed/CMakeLists.txt

# Commit
git commit -m "Add Linux support (VST3/LV2/Standalone) for v0.1.1"

# Push su GitHub
git push origin main
```

## Passo 2: Creare la Release su GitHub

### Opzione A: GitHub Web Interface (Consigliata)

1. Vai su https://github.com/ninuxi/MAI_verb
2. Click su "Releases" (nella sidebar destra)
3. Click su "Draft a new release"
4. Compila il form:

   **Tag version**: `v0.1.1`
   **Release title**: `MAI_verb v0.1.1 - Linux Support`
   
   **Description**: Copia il contenuto di `RELEASE_NOTES_v0.1.1.md`

5. Carica i file nella sezione "Attach binaries":
   - `releases/MAI_verb_v0.1.1_Linux_x64.tar.gz`
   - `releases/MAI_verb_v0.1.1_Linux_x64.zip`
   - (Se disponibile) `releases/MAI_verb_v0.1.1_macOS.zip`

6. Seleziona "Set as the latest release"

7. Click "Publish release"

### Opzione B: GitHub CLI (se installato)

```bash
# Crea la release
gh release create v0.1.1 \
  --title "MAI_verb v0.1.1 - Linux Support" \
  --notes-file RELEASE_NOTES_v0.1.1.md \
  releases/MAI_verb_v0.1.1_Linux_x64.tar.gz \
  releases/MAI_verb_v0.1.1_Linux_x64.zip
```

## Passo 3: Verifica

1. Controlla che la release sia visibile su https://github.com/ninuxi/MAI_verb/releases
2. Scarica il file .tar.gz o .zip per testare
3. Verifica che i link nel README funzionino

## Note

- Il file `.tar.gz` è preferito su Linux (formato nativo)
- Il file `.zip` è compatibile cross-platform
- Assicurati che tutti i link nel README puntino al tag corretto (`v0.1.1`)
- La release può essere modificata successivamente se necessario

## File di Release Preparati

I file sono pronti nella cartella `releases/`:

```bash
ls -lh releases/
```

Dovresti vedere:
- `MAI_verb_v0.1.1_Linux_x64/` (cartella estratta)
- `MAI_verb_v0.1.1_Linux_x64.tar.gz` (per Linux)
- `MAI_verb_v0.1.1_Linux_x64.zip` (cross-platform)
