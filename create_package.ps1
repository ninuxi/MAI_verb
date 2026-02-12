$version = "v0.1.1"
$releaseName = "MAI_verb_${version}_Windows_x64"

Write-Host "Creating release package..." -ForegroundColor Yellow

# Create release directory
New-Item -ItemType Directory -Path "releases\$releaseName" -Force | Out-Null
New-Item -ItemType Directory -Path "releases\$releaseName\Standalone" -Force | Out-Null

# Copy VST3
Write-Host "Copying VST3..."
Copy-Item -Recurse "build\lib\VST3\Bricasti M7.vst3" "releases\$releaseName\"

# Copy Standalone
Write-Host "Copying Standalone..."
Copy-Item "build\bin\Standalone\Bricasti M7.exe" "releases\$releaseName\Standalone\"

# Create INSTALLATION.txt
@"
═══════════════════════════════════════════════════════
  MAI_verb by Mainenti @ aiforlive
  Professional Algorithmic Reverb - Open Source
═══════════════════════════════════════════════════════

🪟 INSTALLAZIONE WINDOWS

╔═══════════════════════════════════════════════════╗
║  INSTALLAZIONE RAPIDA:                            ║
╚═══════════════════════════════════════════════════╝

1️⃣  Estrai il file ZIP scaricato

2️⃣  Installa il plugin VST3:
    - Copia la cartella "Bricasti M7.vst3" in:
      C:\Program Files\Common Files\VST3\

    (Potrebbero essere richiesti permessi amministratore)

3️⃣  Per lo Standalone (opzionale):
    - Esegui "Bricasti M7.exe" dalla cartella Standalone
    - Oppure copia in una cartella a tua scelta

4️⃣  Riavvia la tua DAW (Ableton, FL Studio, Reaper, ecc.)

═══════════════════════════════════════════════════════

📦 FORMATI DISPONIBILI:

✅ VST3       - Per tutte le DAW moderne
✅ Standalone - Applicazione indipendente

═══════════════════════════════════════════════════════

🔧 POSIZIONI ALTERNATIVE:

Se non hai permessi amministratore:
  C:\Users\[TuoNome]\AppData\Local\Programs\Common\VST3\

═══════════════════════════════════════════════════════

🔧 RISOLUZIONE PROBLEMI

Problema: Windows SmartScreen blocca il plugin

Soluzione:
  1. Click destro sul file
  2. Proprietà → Spunta "Sblocca" → Applica
  3. Oppure: Click "Maggiori informazioni" → "Esegui comunque"

Problema: Plugin non appare nella DAW

Soluzione:
  1. Verifica il percorso di installazione
  2. Forza il rescan dei plugin nella DAW
  3. Controlla i log della DAW per errori

Problema: Errore VCRUNTIME140.dll

Soluzione:
  Installa Microsoft Visual C++ Redistributable:
  https://aka.ms/vs/17/release/vc_redist.x64.exe

═══════════════════════════════════════════════════════

📄 LICENZA: Open Source (vedi LICENSE nel repository)
🔗 GitHub: https://github.com/ninuxi/MAI_verb
💬 Issues: https://github.com/ninuxi/MAI_verb/issues
👤 Autore: Mainenti @ aiforlive

═══════════════════════════════════════════════════════
"@ | Out-File -FilePath "releases\$releaseName\INSTALLATION.txt" -Encoding UTF8

# Create ZIP
Write-Host "Creating ZIP archive..."
Compress-Archive -Path "releases\$releaseName" -DestinationPath "releases\${releaseName}.zip" -Force

Write-Host "`nRelease Windows pronta!" -ForegroundColor Green
Write-Host "   releases\${releaseName}.zip" -ForegroundColor Cyan

# Show file size
$zipFile = Get-Item "releases\${releaseName}.zip"
$sizeMB = [math]::Round($zipFile.Length / 1MB, 2)
Write-Host "   Size: $sizeMB MB" -ForegroundColor Cyan
